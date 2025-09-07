#include <catch2/catch_test_macros.hpp>
#include "list.h"

TEST_CASE("PushBack + PopFront дает FIFO-порядок", "[task2][pushback][popfront]") {
    List lst;
    lst.PushBack(1);
    lst.PushBack(2);
    lst.PushBack(3);
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 1);
    REQUIRE(lst.PopFront() == 2);
    REQUIRE(lst.PopFront() == 3);
    REQUIRE(lst.Empty());
}

TEST_CASE("PushFront + PopFront дает LIFO-поведение головы", "[task2][pushfront][popfront]") {
    List lst;
    lst.PushFront(1);
    lst.PushFront(2);
    lst.PushFront(3);
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 3);
    REQUIRE(lst.PopFront() == 2);
    REQUIRE(lst.PopFront() == 1);
    REQUIRE(lst.Empty());
}

TEST_CASE("PopFront/PopBack на пустом списке бросают runtime_error", "[task2][exceptions]") {
    List lst;
    REQUIRE(lst.Empty());
    REQUIRE_THROWS_AS(lst.PopFront(), std::runtime_error);
    REQUIRE_THROWS_AS(lst.PopBack(), std::runtime_error);
    REQUIRE(lst.Size() == 0UL);
}

TEST_CASE("Сложный сценарий чередования операций", "[task2][scenario]") {
    List lst;                 // []
    lst.PushBack(10);         // [10]
    lst.PushFront(5);         // [5, 10]
    lst.PushBack(20);         // [5, 10, 20]
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 5); // [10, 20]
    lst.PushFront(1);             // [1, 10, 20]
    REQUIRE(lst.PopBack() == 20); // [1, 10]
    lst.PushBack(30);             // [1, 10, 30]
    REQUIRE(lst.PopFront() == 1); // [10, 30]
    REQUIRE(lst.PopFront() == 10);// [30]
    REQUIRE(lst.PopBack() == 30); // []
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);

    REQUIRE_THROWS_AS(lst.PopFront(), std::runtime_error);
    REQUIRE_THROWS_AS(lst.PopBack(), std::runtime_error);
}