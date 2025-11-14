#include <string>

#include <chester/engine/file.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_test_macros.hpp>

using chester::engine::file;
using chester::engine::rank;
using chester::engine::square;

// clang-format off

static_assert((square::a1 +   1) == square::b1);
static_assert((square::a1 >>  1) == square::b1);
static_assert((square::a1 +   8) == square::a2);
static_assert((square::a1 >>  8) == square::a2);
static_assert((square::f5 +   8) == square::f6);
static_assert((square::f5 >>  8) == square::f6);
static_assert((square::f5 +   7) == square::e6);
static_assert((square::f5 >>  7) == square::e6);

static_assert((square::h8      ) <  square::high);
static_assert((square::h8 +   1) == square::high);
static_assert((square::h8 >>  1) == square::high);
static_assert((square::h8 +   2) >  square::high);
static_assert((square::h8 >>  2) >  square::high);
static_assert((square::h8 +  10) >  square::high);
static_assert((square::h8 >> 10) >  square::high);

static_assert((square::h8 +   1).invalid());
static_assert((square::h8 >>  1).invalid());
static_assert((square::h8 +   3).invalid());
static_assert((square::h8 >>  3).invalid());
static_assert((square::f8 +   3).invalid());
static_assert((square::f8 >>  3).invalid());
static_assert((square::f8 +   7).invalid());
static_assert((square::f8 >>  7).invalid());
static_assert((square::a1 +  64).invalid());
static_assert((square::a1 >> 64).invalid());
static_assert((square::a1 +  66).invalid());
static_assert((square::a1 >> 66).invalid());

static_assert((square::b1 -   1) == square::a1);
static_assert((square::b1 <<  1) == square::a1);
static_assert((square::a2 -   8) == square::a1);
static_assert((square::a2 <<  8) == square::a1);
static_assert((square::h8 -   8) == square::h7);
static_assert((square::h8 <<  8) == square::h7);
static_assert((square::h8 -   7) == square::a8);
static_assert((square::h8 <<  7) == square::a8);
static_assert((square::h8 -   9) == square::g7);
static_assert((square::h8 <<  9) == square::g7);

static_assert((square::a1      ) >  square::low);
static_assert((square::a1 -   1) == square::low);
static_assert((square::a1 <<  1) == square::low);
static_assert((square::a1 -   2) <  square::low);
static_assert((square::a1 <<  2) <  square::low);
static_assert((square::a1 -  10) <  square::low);
static_assert((square::a1 << 10) <  square::low);

static_assert((square::a1 -   1).invalid());
static_assert((square::a1 <<  1).invalid());
static_assert((square::a1 -   3).invalid());
static_assert((square::a1 <<  3).invalid());
static_assert((square::b1 -   2).invalid());
static_assert((square::b1 <<  2).invalid());
static_assert((square::b1 -   8).invalid());
static_assert((square::b1 <<  8).invalid());
static_assert((square::a2 -   9).invalid());
static_assert((square::a2 <<  9).invalid());
static_assert((square::h8 -  64).invalid());
static_assert((square::h8 << 64).invalid());

TEST_CASE("chester::engine::squares validity", "[engine][square]") {
    for (const auto square : chester::engine::squares) {
        REQUIRE(square.valid());
    }
}

TEST_CASE("chester::engine::square from file and rank", "[engine][square][formatter]") {
    REQUIRE(square::a1 == square(file::a, rank::one));
    REQUIRE(square::a2 == square(file::a, rank::two));
    REQUIRE(square::a3 == square(file::a, rank::three));
    REQUIRE(square::a4 == square(file::a, rank::four));
    REQUIRE(square::a5 == square(file::a, rank::five));
    REQUIRE(square::a6 == square(file::a, rank::six));
    REQUIRE(square::a7 == square(file::a, rank::seven));
    REQUIRE(square::a8 == square(file::a, rank::eight));

    REQUIRE(square::b1 == square(file::b, rank::one));
    REQUIRE(square::b2 == square(file::b, rank::two));
    REQUIRE(square::b3 == square(file::b, rank::three));
    REQUIRE(square::b4 == square(file::b, rank::four));
    REQUIRE(square::b5 == square(file::b, rank::five));
    REQUIRE(square::b6 == square(file::b, rank::six));
    REQUIRE(square::b7 == square(file::b, rank::seven));
    REQUIRE(square::b8 == square(file::b, rank::eight));

    REQUIRE(square::c1 == square(file::c, rank::one));
    REQUIRE(square::c2 == square(file::c, rank::two));
    REQUIRE(square::c3 == square(file::c, rank::three));
    REQUIRE(square::c4 == square(file::c, rank::four));
    REQUIRE(square::c5 == square(file::c, rank::five));
    REQUIRE(square::c6 == square(file::c, rank::six));
    REQUIRE(square::c7 == square(file::c, rank::seven));
    REQUIRE(square::c8 == square(file::c, rank::eight));

    REQUIRE(square::d1 == square(file::d, rank::one));
    REQUIRE(square::d2 == square(file::d, rank::two));
    REQUIRE(square::d3 == square(file::d, rank::three));
    REQUIRE(square::d4 == square(file::d, rank::four));
    REQUIRE(square::d5 == square(file::d, rank::five));
    REQUIRE(square::d6 == square(file::d, rank::six));
    REQUIRE(square::d7 == square(file::d, rank::seven));
    REQUIRE(square::d8 == square(file::d, rank::eight));

    REQUIRE(square::e1 == square(file::e, rank::one));
    REQUIRE(square::e2 == square(file::e, rank::two));
    REQUIRE(square::e3 == square(file::e, rank::three));
    REQUIRE(square::e4 == square(file::e, rank::four));
    REQUIRE(square::e5 == square(file::e, rank::five));
    REQUIRE(square::e6 == square(file::e, rank::six));
    REQUIRE(square::e7 == square(file::e, rank::seven));
    REQUIRE(square::e8 == square(file::e, rank::eight));

    REQUIRE(square::f1 == square(file::f, rank::one));
    REQUIRE(square::f2 == square(file::f, rank::two));
    REQUIRE(square::f3 == square(file::f, rank::three));
    REQUIRE(square::f4 == square(file::f, rank::four));
    REQUIRE(square::f5 == square(file::f, rank::five));
    REQUIRE(square::f6 == square(file::f, rank::six));
    REQUIRE(square::f7 == square(file::f, rank::seven));
    REQUIRE(square::f8 == square(file::f, rank::eight));

    REQUIRE(square::g1 == square(file::g, rank::one));
    REQUIRE(square::g2 == square(file::g, rank::two));
    REQUIRE(square::g3 == square(file::g, rank::three));
    REQUIRE(square::g4 == square(file::g, rank::four));
    REQUIRE(square::g5 == square(file::g, rank::five));
    REQUIRE(square::g6 == square(file::g, rank::six));
    REQUIRE(square::g7 == square(file::g, rank::seven));
    REQUIRE(square::g8 == square(file::g, rank::eight));

    REQUIRE(square::h1 == square(file::h, rank::one));
    REQUIRE(square::h2 == square(file::h, rank::two));
    REQUIRE(square::h3 == square(file::h, rank::three));
    REQUIRE(square::h4 == square(file::h, rank::four));
    REQUIRE(square::h5 == square(file::h, rank::five));
    REQUIRE(square::h6 == square(file::h, rank::six));
    REQUIRE(square::h7 == square(file::h, rank::seven));
    REQUIRE(square::h8 == square(file::h, rank::eight));
}

TEST_CASE("std::to_string(chester::engine::square)", "[engine][square][fmt]") {
    REQUIRE("a1" == std::to_string(square::a1));
    REQUIRE("a2" == std::to_string(square::a2));
    REQUIRE("a3" == std::to_string(square::a3));
    REQUIRE("a4" == std::to_string(square::a4));
    REQUIRE("a5" == std::to_string(square::a5));
    REQUIRE("a6" == std::to_string(square::a6));
    REQUIRE("a7" == std::to_string(square::a7));
    REQUIRE("a8" == std::to_string(square::a8));

    REQUIRE("b1" == std::to_string(square::b1));
    REQUIRE("b2" == std::to_string(square::b2));
    REQUIRE("b3" == std::to_string(square::b3));
    REQUIRE("b4" == std::to_string(square::b4));
    REQUIRE("b5" == std::to_string(square::b5));
    REQUIRE("b6" == std::to_string(square::b6));
    REQUIRE("b7" == std::to_string(square::b7));
    REQUIRE("b8" == std::to_string(square::b8));

    REQUIRE("c1" == std::to_string(square::c1));
    REQUIRE("c2" == std::to_string(square::c2));
    REQUIRE("c3" == std::to_string(square::c3));
    REQUIRE("c4" == std::to_string(square::c4));
    REQUIRE("c5" == std::to_string(square::c5));
    REQUIRE("c6" == std::to_string(square::c6));
    REQUIRE("c7" == std::to_string(square::c7));
    REQUIRE("c8" == std::to_string(square::c8));

    REQUIRE("d1" == std::to_string(square::d1));
    REQUIRE("d2" == std::to_string(square::d2));
    REQUIRE("d3" == std::to_string(square::d3));
    REQUIRE("d4" == std::to_string(square::d4));
    REQUIRE("d5" == std::to_string(square::d5));
    REQUIRE("d6" == std::to_string(square::d6));
    REQUIRE("d7" == std::to_string(square::d7));
    REQUIRE("d8" == std::to_string(square::d8));

    REQUIRE("e1" == std::to_string(square::e1));
    REQUIRE("e2" == std::to_string(square::e2));
    REQUIRE("e3" == std::to_string(square::e3));
    REQUIRE("e4" == std::to_string(square::e4));
    REQUIRE("e5" == std::to_string(square::e5));
    REQUIRE("e6" == std::to_string(square::e6));
    REQUIRE("e7" == std::to_string(square::e7));
    REQUIRE("e8" == std::to_string(square::e8));

    REQUIRE("f1" == std::to_string(square::f1));
    REQUIRE("f2" == std::to_string(square::f2));
    REQUIRE("f3" == std::to_string(square::f3));
    REQUIRE("f4" == std::to_string(square::f4));
    REQUIRE("f5" == std::to_string(square::f5));
    REQUIRE("f6" == std::to_string(square::f6));
    REQUIRE("f7" == std::to_string(square::f7));
    REQUIRE("f8" == std::to_string(square::f8));

    REQUIRE("g1" == std::to_string(square::g1));
    REQUIRE("g2" == std::to_string(square::g2));
    REQUIRE("g3" == std::to_string(square::g3));
    REQUIRE("g4" == std::to_string(square::g4));
    REQUIRE("g5" == std::to_string(square::g5));
    REQUIRE("g6" == std::to_string(square::g6));
    REQUIRE("g7" == std::to_string(square::g7));
    REQUIRE("g8" == std::to_string(square::g8));

    REQUIRE("h1" == std::to_string(square::h1));
    REQUIRE("h2" == std::to_string(square::h2));
    REQUIRE("h3" == std::to_string(square::h3));
    REQUIRE("h4" == std::to_string(square::h4));
    REQUIRE("h5" == std::to_string(square::h5));
    REQUIRE("h6" == std::to_string(square::h6));
    REQUIRE("h7" == std::to_string(square::h7));
    REQUIRE("h8" == std::to_string(square::h8));
}
