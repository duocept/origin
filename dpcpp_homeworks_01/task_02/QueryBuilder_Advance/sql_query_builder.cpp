#include "sql_query_builder.h"
#include <sstream>

// Добавление колонки
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column) noexcept {
    columns_.push_back(column);
    return *this;
}

// Установка таблицы (перезаписывает прошлое значение)
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) noexcept {
    from_ = table;
    return *this;
}

// Добавление условия WHERE column = value
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& column,
    const std::string& value) noexcept
{
    where_.emplace_back(column, value);
    return *this;
}

// === Задание 2 ===

// Добавить сразу несколько колонок
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(
    const std::vector<std::string>& columns) noexcept
{
    for (const auto& col : columns) {
        AddColumn(col);  // используем уже существующий метод
    }
    return *this;
}

// Добавить сразу несколько условий WHERE
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(
    const std::map<std::string, std::string>& kv) noexcept
{
    for (const auto& item : kv) {
        // item.first  - имя колонки
        // item.second - значение
        AddWhere(item.first, item.second);  // снова переиспользуем базовый AddWhere
    }
    return *this;
}


// Сборка итогового SQL
std::string SqlSelectQueryBuilder::BuildQuery() const {
    std::ostringstream query;

    // 1) SELECT
    query << "SELECT ";
    if (columns_.empty()) {
        // если ни одной колонки не добавлено — SELECT *
        query << "*";
    }
    else {
        for (std::size_t i = 0; i < columns_.size(); ++i) {
            if (i > 0) {
                query << ", ";
            }
            query << columns_[i];
        }
    }

    // 2) FROM
    if (!from_.empty()) {
        query << " FROM " << from_;
    }

    // 3) WHERE
    if (!where_.empty()) {
        query << " WHERE ";
        for (std::size_t i = 0; i < where_.size(); ++i) {
            if (i > 0) {
                query << " AND ";
            }
            // по условию ДЗ кавычки для строк не используем
            query << where_[i].first << "=" << where_[i].second;
        }
    }

    // 4) ; в конце
    query << ";";
    return query.str();
}
