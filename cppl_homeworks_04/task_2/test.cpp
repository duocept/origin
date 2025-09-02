#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "list.cpp"

TEST_CASE("PushBack: элементы уходят в хвост; порядок FIFO через PopFront", "[list][pushback][popfront]") {
    List lst;
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);

    lst.PushBack(1);
    lst.PushBack(2);
    lst.PushBack(3);
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 1);
    REQUIRE(lst.Size() == 2UL);
    REQUIRE(lst.PopFront() == 2);
    REQUIRE(lst.Size() == 1UL);
    REQUIRE(lst.PopFront() == 3);
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);
}

TEST_CASE("PushFront: элементы уходят в голову; порядок LIFO через PopFront", "[list][pushfront][popfront]") {
    List lst;

    lst.PushFront(1);
    lst.PushFront(2);
    lst.PushFront(3);
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 3);
    REQUIRE(lst.Size() == 2UL);
    REQUIRE(lst.PopFront() == 2);
    REQUIRE(lst.Size() == 1UL);
    REQUIRE(lst.PopFront() == 1);
    REQUIRE(lst.Empty());
}

TEST_CASE("PopBack/PopFront на пустом списке бросают runtime_error", "[list][empty][exceptions]") {
    List lst;
    REQUIRE(lst.Empty());

    REQUIRE_THROWS_WITH(lst.PopFront(), "list is empty");
    REQUIRE_THROWS_WITH(lst.PopBack(), "list is empty");
    REQUIRE(lst.Size() == 0UL); // размер не изменился
}

TEST_CASE("Сложный сценарий: чередование операций Push/Pop спереди и сзади", "[list][scenario]") {
    List lst;
    // Старт: []
    lst.PushBack(10);                 // [10]
    REQUIRE(lst.Size() == 1UL);

    lst.PushFront(5);                 // [5, 10]
    REQUIRE(lst.Size() == 2UL);

    lst.PushBack(20);                 // [5, 10, 20]
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 5);     // [10, 20]
    REQUIRE(lst.Size() == 2UL);

    lst.PushFront(1);                 // [1, 10, 20]
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopBack() == 20);     // [1, 10]
    REQUIRE(lst.Size() == 2UL);

    lst.PushBack(30);                 // [1, 10, 30]
    REQUIRE(lst.Size() == 3UL);

    REQUIRE(lst.PopFront() == 1);     // [10, 30]
    REQUIRE(lst.Size() == 2UL);

    REQUIRE(lst.PopFront() == 10);    // [30]
    REQUIRE(lst.Size() == 1UL);

    REQUIRE(lst.PopBack() == 30);     // []
    REQUIRE(lst.Empty());
    REQUIRE(lst.Size() == 0UL);

    // убедимся, что на пустом снова бросает
    REQUIRE_THROWS_WITH(lst.PopFront(), "list is empty");
    REQUIRE_THROWS_WITH(lst.PopBack(), "list is empty");
}