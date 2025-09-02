#include <catch2/catch_test_macros.hpp>
#include "list.cpp"

TEST_CASE("Empty() и Size() на свежем списке", "[list][empty][size]") {
    List lst;
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);
}

TEST_CASE("Size() корректно растёт при добавлениях", "[list][size]") {
    List lst;

    lst.PushFront(10);
    REQUIRE_FALSE(lst.Empty());
    REQUIRE(lst.Size() == 1UL);

    lst.PushBack(20);
    REQUIRE(lst.Size() == 2UL);

    for (int i = 0; i < 5; ++i) lst.PushBack(i);
    REQUIRE(lst.Size() == 7UL);
}

TEST_CASE("Clear() очищает список и оставляет его работоспособным", "[list][clear]") {
    List lst;

    for (int i = 0; i < 5; ++i) lst.PushBack(i);
    REQUIRE(lst.Size() == 5UL);

    lst.Clear();
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);

    REQUIRE_NOTHROW(lst.Clear());
    REQUIRE(lst.Size() == 0UL);

    lst.PushFront(42);
    lst.PushBack(7);
    REQUIRE_FALSE(lst.Empty());
    REQUIRE(lst.Size() == 2UL);

    lst.Clear();
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);
}