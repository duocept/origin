#include <iostream>
#include <map>
#include <vector>
#include "sql_query_builder.h"

int main() {
    SqlSelectQueryBuilder qb;

    qb.AddColumns({ "name", "phone", "email" })       // добавили сразу три колонки
        .AddFrom("students")
        .AddWhere({                                   // добавили сразу два условия
            {"id", "42"},
            {"name", "John"}
            });

    std::string sql = qb.BuildQuery();
    std::cout << sql << std::endl;

    // Ожидаемо:
    // SELECT name, phone, email FROM students WHERE id=42 AND name=John;

    return 0;
}
