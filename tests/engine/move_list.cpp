#include <catch2/catch_test_macros.hpp>

#include <chester/move.hpp>
#include <chester/move_list.hpp>
#include <chester/move_type.hpp>
#include <chester/square.hpp>

using chester::move;
using chester::move_list;
using chester::move_type;
using chester::square;

// clang-format off

TEST_CASE("chester::move_list::pop order", "[engine][move list]") {
    move a = move(square::a1, square::a2, move_type::normal);
    move b = move(square::b1, square::b2, move_type::normal);
    move c = move(square::c1, square::c2, move_type::normal);

    move_list move_list;

    move_list.push(a, 3);
    move_list.push(b, 1);
    move_list.push(c, 2);

    REQUIRE(move_list.pop() == a);
    REQUIRE(move_list.pop() == c);
    REQUIRE(move_list.pop() == b);
}

TEST_CASE("chester::move_list::size", "[engine][move list]") {
    move a = move(square::a1, square::a2, move_type::normal);
    move b = move(square::b1, square::b2, move_type::normal);
    move c = move(square::c1, square::c2, move_type::normal);

    move_list move_list;


    WHEN("move list is empty") {
        REQUIRE(0 == move_list.size());
    }

    WHEN("move list has one move") {
        move_list.push(a, 3);
        REQUIRE(1 == move_list.size());
    }

    WHEN("move list has two moves") {
        move_list.push(a, 3);
        move_list.push(b, 1);
        REQUIRE(2 == move_list.size());
    }

    WHEN("move list has three moves") {
        move_list.push(a, 3);
        move_list.push(b, 1);
        move_list.push(c, 2);
        REQUIRE(3 == move_list.size());
    }

    WHEN("move list has two moves after one pop()") {
        move_list.push(a, 3);
        move_list.push(b, 1);
        move_list.push(c, 2);
        move_list.pop();
        REQUIRE(2 == move_list.size());
    }

    WHEN("move list has one moves after two pop()s") {
        move_list.push(a, 3);
        move_list.push(b, 1);
        move_list.push(c, 2);
        move_list.pop();
        move_list.pop();
        REQUIRE(1 == move_list.size());
    }

    WHEN("move list has no moves after three pop()s") {
        move_list.push(a, 3);
        move_list.push(b, 1);
        move_list.push(c, 2);
        move_list.pop();
        move_list.pop();
        move_list.pop();
        REQUIRE(0 == move_list.size());
    }
}
