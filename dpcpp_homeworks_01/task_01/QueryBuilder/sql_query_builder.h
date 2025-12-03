#pragma once

#include <string>
#include <vector>
#include <utility>

class SqlSelectQueryBuilder {
public:
    // Добавляет одну колонку в SELECT
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept;

    // Устанавливает таблицу (каждый новый вызов перезаписывает предыдущее значение)
    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept;

    // Добавляет одно условие WHERE: column = value
    SqlSelectQueryBuilder& AddWhere(const std::string& column,
        const std::string& value) noexcept;

    // Собирает готовый SQL-запрос
    std::string BuildQuery() const;

private:
    std::vector<std::string> columns_;                        // поля в SELECT
    std::string from_;                                        // таблица
    std::vector<std::pair<std::string, std::string>> where_;  // условия WHERE
};
