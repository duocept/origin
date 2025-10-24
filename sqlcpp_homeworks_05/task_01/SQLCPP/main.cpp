#include <pqxx/pqxx>
#include <iostream>
#include <optional>
#include <vector>
#include <tuple>
#include <sstream>

struct Client {
    long long id{};
    std::string first_name;
    std::string last_name;
    std::string email;
};

class ClientDB {
public:
    explicit ClientDB(const std::string& conn_str)
        : conn_{ conn_str } {
        if (!conn_.is_open()) {
            throw std::runtime_error("Unable to open DB connection");
        }
    }

    // 1) Создание структуры БД (таблиц)
    void create_schema() {
        pqxx::work tx{ conn_ };
        tx.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS clients (
                id          BIGSERIAL PRIMARY KEY,
                first_name  TEXT        NOT NULL,
                last_name   TEXT        NOT NULL,
                email       TEXT        NOT NULL,
                created_at  TIMESTAMPTZ NOT NULL DEFAULT now(),
                CONSTRAINT email_not_empty CHECK (length(trim(email)) > 0)
            );
        )SQL");
        tx.exec(R"SQL(
            CREATE UNIQUE INDEX IF NOT EXISTS ux_clients_email_ci ON clients (lower(email));
        )SQL");
        tx.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS phones (
                id         BIGSERIAL PRIMARY KEY,
                client_id  BIGINT NOT NULL REFERENCES clients(id) ON DELETE CASCADE,
                phone      TEXT   NOT NULL,
                label      TEXT   DEFAULT NULL,
                CONSTRAINT phone_not_empty CHECK (length(trim(phone)) > 0),
                CONSTRAINT ux_phone UNIQUE (phone)
            );
        )SQL");
        tx.exec(R"SQL(
            CREATE INDEX IF NOT EXISTS ix_phones_client ON phones(client_id);
        )SQL");
        tx.commit();
    }

    // 2) Добавить нового клиента — возвращает id
    long long add_client(const std::string& first,
        const std::string& last,
        const std::string& email)
    {
        pqxx::work tx{ conn_ };
        auto r = tx.exec_params(
            "INSERT INTO clients(first_name, last_name, email) VALUES($1,$2,lower($3)) RETURNING id",
            first, last, email);
        long long id = r[0][0].as<long long>();
        tx.commit();
        return id;
    }

    // 3) Добавить телефон существующему клиенту
    void add_phone(long long client_id, const std::string& phone, std::optional<std::string> label = std::nullopt) {
        pqxx::work tx{ conn_ };
        // Проверим, что клиент существует
        {
            auto r = tx.exec_params("SELECT 1 FROM clients WHERE id=$1", client_id);
            if (r.empty()) {
                throw std::runtime_error("Client not found");
            }
        }
        if (label.has_value()) {
            tx.exec_params("INSERT INTO phones(client_id, phone, label) VALUES($1, $2, $3)",
                client_id, phone, *label);
        }
        else {
            tx.exec_params("INSERT INTO phones(client_id, phone) VALUES($1, $2)",
                client_id, phone);
        }
        tx.commit();
    }

    // 4) Изменить данные о клиенте (частичное обновление)
    void update_client(long long client_id,
        std::optional<std::string> first = std::nullopt,
        std::optional<std::string> last = std::nullopt,
        std::optional<std::string> email = std::nullopt)
    {
        if (!first && !last && !email) return; // нечего обновлять

        pqxx::work tx{ conn_ };
        std::ostringstream set_sql;
        set_sql << "UPDATE clients SET ";

        bool first_field = true;
        if (first) {
            set_sql << (first_field ? "" : ", ") << "first_name = " << tx.quote(*first);
            first_field = false;
        }
        if (last) {
            set_sql << (first_field ? "" : ", ") << "last_name = " << tx.quote(*last);
            first_field = false;
        }
        if (email) {
            set_sql << (first_field ? "" : ", ") << "email = lower(" << tx.quote(*email) << ")";
            first_field = false;
        }
        set_sql << " WHERE id = " << client_id << " RETURNING id;";

        auto r = tx.exec(set_sql.str());
        if (r.empty()) {
            throw std::runtime_error("Client not found");
        }
        tx.commit();
    }

    // 5) Удалить телефон клиента
    void delete_phone(long long client_id, const std::string& phone) {
        pqxx::work tx{ conn_ };
        auto r = tx.exec_params("DELETE FROM phones WHERE client_id=$1 AND phone=$2 RETURNING id",
            client_id, phone);
        if (r.empty()) {
            throw std::runtime_error("Phone not found for this client");
        }
        tx.commit();
    }

    // 6) Удалить клиента
    void delete_client(long long client_id) {
        pqxx::work tx{ conn_ };
        auto r = tx.exec_params("DELETE FROM clients WHERE id=$1 RETURNING id", client_id);
        if (r.empty()) {
            throw std::runtime_error("Client not found");
        }
        tx.commit();
    }

    // 7) Поиск клиентов

    // По имени и фамилии (ILIKE — частичное, нечувствительное к регистру)
    std::vector<Client> find_by_name(std::string first, std::string last) {
        pqxx::work tx{ conn_ };
        auto res = tx.exec_params(
            "SELECT id, first_name, last_name, email "
            "FROM clients WHERE first_name ILIKE $1 AND last_name ILIKE $2 "
            "ORDER BY id",
            first, last);
        tx.commit();
        return rows_to_clients(res);
    }

    // По email (точное совпадение, регистронезависимо)
    std::optional<Client> find_by_email(std::string email) {
        pqxx::work tx{ conn_ };
        // Пример использования transaction_base::query (если у вас свежая pqxx):
        // auto rows = tx.query<std::tuple<long long,std::string,std::string,std::string>>(
        //   "SELECT id, first_name, last_name, email FROM clients WHERE lower(email)=lower("
        //   + tx.quote(email) + ") LIMIT 1");
        // if (!rows.empty()) { ... }

        auto res = tx.exec_params(
            "SELECT id, first_name, last_name, email "
            "FROM clients WHERE lower(email)=lower($1) LIMIT 1",
            email);
        tx.commit();

        if (res.empty()) return std::nullopt;
        return Client{
            res[0][0].as<long long>(),
            res[0][1].as<std::string>(),
            res[0][2].as<std::string>(),
            res[0][3].as<std::string>()
        };
    }

    // По телефону (JOIN)
    std::vector<Client> find_by_phone(std::string phone) {
        pqxx::work tx{ conn_ };
        auto res = tx.exec_params(
            "SELECT c.id, c.first_name, c.last_name, c.email "
            "FROM clients c "
            "JOIN phones p ON p.client_id = c.id "
            "WHERE p.phone = $1 "
            "ORDER BY c.id",
            phone);
        tx.commit();
        return rows_to_clients(res);
    }

private:
    pqxx::connection conn_;

    static std::vector<Client> rows_to_clients(const pqxx::result& res) {
        std::vector<Client> out;
        out.reserve(res.size());
        for (auto const& row : res) {
            out.push_back(Client{
                row["id"].as<long long>(),
                row["first_name"].as<std::string>(),
                row["last_name"].as<std::string>(),
                row["email"].as<std::string>()
                });
        }
        return out;
    }
};

int main() {

    try {
        // Укажите свою строку подключения: postgresql://пользователь:пароль@хост:порт/название БД
        // Пример: "postgresql://postgres:postgres@localhost:5432/clientsdb"
        const std::string conn_str = std::getenv("PG_CONN")
            ? std::getenv("PG_CONN")
            : "postgresql://postgres:password@localhost:5432/clientsdb";

        ClientDB db{ conn_str };
        db.create_schema();

        // === Демонстрация ===

        // Добавим клиентов
        auto alice_id = db.add_client("Alice", "Wonder", "Alice@example.com");
        auto bob_id = db.add_client("Bob", "Marley", "bob@music.org");

        // Телефоны
        db.add_phone(alice_id, "+1 202 555-0147", "mobile");
        db.add_phone(alice_id, "+1 202 555-0110", "work");
        db.add_phone(bob_id, "+44 20 7946 0991", "mobile");

        // Изменение клиента
        db.update_client(alice_id, std::nullopt, std::string("Wonderland"), std::nullopt);

        // Поиск по email
        if (auto alice = db.find_by_email("alice@example.com"); alice) {
            std::cout << "Found by email: " << alice->id << " "
                << alice->first_name << " " << alice->last_name
                << " <" << alice->email << ">\n";
        }

        // Поиск по телефону
        for (auto& c : db.find_by_phone("+44 20 7946 0991")) {
            std::cout << "Found by phone: " << c.id << " "
                << c.first_name << " " << c.last_name
                << " <" << c.email << ">\n";
        }

        // Поиск по имени
        for (auto& c : db.find_by_name("%ob%", "%ar%")) { // частичный поиск ILIKE
            std::cout << "Found by name: " << c.id << " "
                << c.first_name << " " << c.last_name << "\n";
        }

        // Удалим телефон
        db.delete_phone(alice_id, "+1 202 555-0110");

        // Удалим клиента Боба — его телефоны удалятся каскадно
        db.delete_client(bob_id);

        std::cout << "Demo completed.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERR] " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
