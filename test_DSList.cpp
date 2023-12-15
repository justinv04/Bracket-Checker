#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "DSList.cpp"


TEST_CASE("Check that DSList works", "[DSList]")
{
    DSList<int> list = DSList<int>();
    REQUIRE(list.isEmpty());
    REQUIRE(list.getSize() == 0);

    // test push_front
    list.push_front(1);
    REQUIRE(!list.isEmpty());
    REQUIRE(list.getSize() == 1);
    REQUIRE(list.pop_front() == 1);

    // test push_back
    list.push_back(2);
    REQUIRE(!list.isEmpty());
    REQUIRE(list.getSize() == 1);
    REQUIRE(list.pop_front() == 2);

    // test pop_front and pop_back on empty list
    CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
    CHECK_THROWS_AS(list.pop_back(), std::out_of_range);

    // test pop_front and pop_back on non-empty list
    list.push_back(3);
    list.push_back(4);
    REQUIRE(list.pop_front() == 3);
    REQUIRE(list.pop_back() == 4);

    // test find on empty list
    REQUIRE(list.find(1) == -1);

    // test find on non-empty list
    list.push_back(5);
    REQUIRE(list.find(5) == 0);
    REQUIRE(list.find(3) == -1);

    // test copy constructor and assignment operator
    DSList<int> list2(list);
    REQUIRE(list2.getSize() == 1);
    REQUIRE(list2.pop_front() == 5);

    DSList<int> list3 = list;
    REQUIRE(list3.getSize() == 1);
    REQUIRE(list3.pop_front() == 5);

    // test clear
    list.clear();
    REQUIRE(list.isEmpty());
    REQUIRE(list.getSize() == 0);
}
