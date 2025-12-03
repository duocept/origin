#include <iostream>
#include "sql_query_builder.h"

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::string sql = query_builder.BuildQuery();
    std::cout << sql << std::endl;

    // Ожидаемый вывод:
    // SELECT name, phone FROM students WHERE id=42 AND name=John;

    return 0;
}
