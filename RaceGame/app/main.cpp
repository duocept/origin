#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_set>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Race.h"
#include "vehicles/Camel.h"
#include "vehicles/CamelFast.h"
#include "vehicles/Centaur.h"
#include "vehicles/AllTerrainBoots.h"
#include "vehicles/Carpet.h"
#include "vehicles/Eagle.h"
#include "vehicles/Broom.h"

namespace ui {

int ask_int(const std::string& prompt, int min_val, int max_val) {
    int v;
    for (;;) {
        std::cout << prompt;
        if (std::cin >> v && v >= min_val && v <= max_val) return v;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Попробуйте ещё раз.\n";
    }
}

double ask_double_positive(const std::string& prompt) {
    double v;
    for (;;) {
        std::cout << prompt;
        if (std::cin >> v && v > 0.0) return v;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректное расстояние. Введите положительное число.\n";
    }
}

int vehicle_menu_size(RaceType type) {
    int cnt = 0;
    if (type != RaceType::Air)  cnt += 4; // наземные
    if (type != RaceType::Land) cnt += 3; // воздушные
    return cnt;                  // Mixed -> 7, Land -> 4, Air -> 3
}

void print_vehicle_menu(RaceType type, const std::unordered_set<std::string>& disabled) {
    std::cout << "Доступные транспортные средства:\n";
    int idx = 1;
    auto print_item = [&](const std::string& n, bool show) {
        if (show) {
            std::cout << "  " << idx << ". " << n;
            if (disabled.count(n)) std::cout << " (уже зарегистрирован)";
            std::cout << "\n";
            ++idx;
        }
    };

    // Land
    print_item("Верблюд", type != RaceType::Air);
    print_item("Верблюд-быстроход", type != RaceType::Air);
    print_item("Кентавр", type != RaceType::Air);
    print_item("Ботинки-вездеходы", type != RaceType::Air);
    // Air
    print_item("Ковёр-самолёт", type != RaceType::Land);
    print_item("Орёл", type != RaceType::Land);
    print_item("Метла", type != RaceType::Land);
}

std::shared_ptr<Vehicle> make_vehicle_by_index(RaceType type, int choice) {
    // Build list matching the print order
    std::vector<std::function<std::shared_ptr<Vehicle>()>> builders;
    if (type != RaceType::Air) {
        builders.push_back([]{ return std::make_shared<Camel>(); });
        builders.push_back([]{ return std::make_shared<CamelFast>(); });
        builders.push_back([]{ return std::make_shared<Centaur>(); });
        builders.push_back([]{ return std::make_shared<AllTerrainBoots>(); });
    }
    if (type != RaceType::Land) {
        builders.push_back([]{ return std::make_shared<Carpet>(); });
        builders.push_back([]{ return std::make_shared<Eagle>(); });
        builders.push_back([]{ return std::make_shared<Broom>(); });
    }
    if (choice < 1 || choice > static_cast<int>(builders.size())) return nullptr;
    return builders[choice - 1]();
}

} // namespace ui

bool register_vehicle_interactive(Race& race, RaceType type) {
    // Если сможете получить имена уже зарегистрированных ТС из Race — заполните disabled
    std::unordered_set<std::string> disabled;
    // for (const auto& n : race.registered_vehicle_names()) disabled.insert(n);

    ui::print_vehicle_menu(type, disabled);

    const int max_option = ui::vehicle_menu_size(type);
    if (max_option == 0) {
        std::cout << "Для этого типа гонки нет доступных ТС.\n";
        return false;
    }

    const int idx = ui::ask_int("Выберите ТС по номеру: ", 1, max_option);
    auto v = ui::make_vehicle_by_index(type, idx);
    if (!v) {
        std::cout << "Нет такого ТС.\n";
        return false;
    }

    if (!race.register_vehicle(v)) {
        std::cout << "Нельзя зарегистрировать это ТС (либо уже зарегистрировано, либо тип гонки не подходит).\n";
        return false;
    }

    std::cout << "Зарегистрирован: " << v->name() << "\n";
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(2);

    for (;;) {
        std::cout << "Добро пожаловать в гоночный симулятор!\n";
        std::cout << "  1. Гонка для наземного транспорта\n";
        std::cout << "  2. Гонка для воздушного транспорта\n";
        std::cout << "  3. Гонка для наземного и воздушного транспорта\n";

        int race_choice = ui::ask_int("Выберите тип гонки: ", 1, 3);
        RaceType type = static_cast<RaceType>(race_choice);

        double distance = ui::ask_double_positive("Укажите длину дистанции (должна быть положительна): ");

        Race race(type);

        for (;;) {
            if (race.participants_count() < 2) {
                std::cout << "Для начала гонки необходимо зарегистрировать минимум два ТС.\n";
                std::cout << "  1. Зарегистрировать транспорт\n";
                int action = ui::ask_int("Выберите действие: ", 1, 1);
                if (action == 1){
                    (void)register_vehicle_interactive(race, type);
                }
            }
            else {

                std::cout << "\nВыберите действие:\n";
                std::cout << "  1. Зарегистрировать транспорт\n";
                std::cout << "  2. Начать гонку\n";
                std::cout << "  0. Выход\n";
                int action = ui::ask_int("Выберите действие: ", 0, 2);

                if (action == 0) {
                    std::cout << "До встречи!\n";
                    return 0;
                }
                else if (action == 2) {
                    if (race.participants_count() < 2) {
                        std::cout << "Для начала гонки необходимо зарегистрировать минимум два ТС.\n";
                        continue;
                    }
                    auto results = race.start(distance);
                    std::cout << "\nРезультаты гонки на " << distance << " км:\n";
                    int place = 1;
                    for (const auto& r : results) {
                        std::cout << "  " << place++ << ". " << r.vehicle_name
                            << " — " << r.time_hours << " ч\n";
                    }
                    std::cout << "\nПровести ещё одну гонку? (1 — да, 0 — нет): ";
                    int again = ui::ask_int("", 0, 1);
                    if (again == 1) {
                        std::cout << "\n--------------------------------------\n\n";
                        break; // restart outer loop
                    }
                    else {
                        std::cout << "До встречи!\n";
                        return 0;
                    }
                }
                else {
                    (void)register_vehicle_interactive(race, type);
                }
            }
        }
    }
}
