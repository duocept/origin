#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>      // <-- добавил

class SqlSelectQueryBuilder {
public:
    // Базовые методы (Задание 1)
    // 
    // Добавляет одну колонку в SELECT
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept;

    // Устанавливает таблицу (каждый новый вызов перезаписывает предыдущее значение)
    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept;

    // Добавляет одно условие WHERE: column = value
    SqlSelectQueryBuilder& AddWhere(const std::string& column,
        const std::string& value) noexcept;

    // === Задание 2 ===

    // Добавить сразу несколько колонок
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;

    // Добавить сразу несколько условий WHERE (аналог нескольких AddWhere)
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;

    // Собирает готовый SQL-запрос
    std::string BuildQuery() const;

private:
    std::vector<std::string> columns_;                        // поля в SELECT
    std::string from_;                                        // таблица
    std::vector<std::pair<std::string, std::string>> where_;  // условия WHERE
};