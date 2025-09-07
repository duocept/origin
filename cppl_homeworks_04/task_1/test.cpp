#include <catch2/catch_test_macros.hpp>
#include "list.h"

TEST_CASE("Свежесозданный список пуст", "[task1][empty][size]") {
    List lst;
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);
}

TEST_CASE("Size растет при вставках", "[task1][size]") {
    List lst;
    lst.PushFront(10);
    REQUIRE_FALSE(lst.Empty());
    REQUIRE(lst.Size() == 1UL);

    lst.PushBack(20);
    REQUIRE(lst.Size() == 2UL);

    for (int i = 0; i < 5; ++i) lst.PushBack(i);
    REQUIRE(lst.Size() == 7UL);
}

TEST_CASE("Clear очищает список и позволяет дальше работать", "[task1][clear]") {
    List lst;
    for (int i = 0; i < 5; ++i) lst.PushBack(i);
    REQUIRE(lst.Size() == 5UL);

    lst.Clear();
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);

    // Повторный Clear безопасен
    REQUIRE_NOTHROW(lst.Clear());
    REQUIRE(lst.Size() == 0UL);

    // После очистки можно снова вставлять
    lst.PushFront(42);
    lst.PushBack(7);
    REQUIRE_FALSE(lst.Empty());
    REQUIRE(lst.Size() == 2UL);
}
