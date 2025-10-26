// clang-format off

#include <format>

#include <chester/engine/square.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/file.hpp>

#include <catch2/catch_test_macros.hpp>

using chester::engine::square;
using chester::engine::file;
using chester::engine::rank;

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

TEST_CASE("chester::engine::square formatter", "[engine][square][fmt]") {
    REQUIRE("a1" == std::format("{}", square::a1));
    REQUIRE("a2" == std::format("{}", square::a2));
    REQUIRE("a3" == std::format("{}", square::a3));
    REQUIRE("a4" == std::format("{}", square::a4));
    REQUIRE("a5" == std::format("{}", square::a5));
    REQUIRE("a6" == std::format("{}", square::a6));
    REQUIRE("a7" == std::format("{}", square::a7));
    REQUIRE("a8" == std::format("{}", square::a8));

    REQUIRE("b1" == std::format("{}", square::b1));
    REQUIRE("b2" == std::format("{}", square::b2));
    REQUIRE("b3" == std::format("{}", square::b3));
    REQUIRE("b4" == std::format("{}", square::b4));
    REQUIRE("b5" == std::format("{}", square::b5));
    REQUIRE("b6" == std::format("{}", square::b6));
    REQUIRE("b7" == std::format("{}", square::b7));
    REQUIRE("b8" == std::format("{}", square::b8));

    REQUIRE("c1" == std::format("{}", square::c1));
    REQUIRE("c2" == std::format("{}", square::c2));
    REQUIRE("c3" == std::format("{}", square::c3));
    REQUIRE("c4" == std::format("{}", square::c4));
    REQUIRE("c5" == std::format("{}", square::c5));
    REQUIRE("c6" == std::format("{}", square::c6));
    REQUIRE("c7" == std::format("{}", square::c7));
    REQUIRE("c8" == std::format("{}", square::c8));

    REQUIRE("d1" == std::format("{}", square::d1));
    REQUIRE("d2" == std::format("{}", square::d2));
    REQUIRE("d3" == std::format("{}", square::d3));
    REQUIRE("d4" == std::format("{}", square::d4));
    REQUIRE("d5" == std::format("{}", square::d5));
    REQUIRE("d6" == std::format("{}", square::d6));
    REQUIRE("d7" == std::format("{}", square::d7));
    REQUIRE("d8" == std::format("{}", square::d8));

    REQUIRE("e1" == std::format("{}", square::e1));
    REQUIRE("e2" == std::format("{}", square::e2));
    REQUIRE("e3" == std::format("{}", square::e3));
    REQUIRE("e4" == std::format("{}", square::e4));
    REQUIRE("e5" == std::format("{}", square::e5));
    REQUIRE("e6" == std::format("{}", square::e6));
    REQUIRE("e7" == std::format("{}", square::e7));
    REQUIRE("e8" == std::format("{}", square::e8));

    REQUIRE("f1" == std::format("{}", square::f1));
    REQUIRE("f2" == std::format("{}", square::f2));
    REQUIRE("f3" == std::format("{}", square::f3));
    REQUIRE("f4" == std::format("{}", square::f4));
    REQUIRE("f5" == std::format("{}", square::f5));
    REQUIRE("f6" == std::format("{}", square::f6));
    REQUIRE("f7" == std::format("{}", square::f7));
    REQUIRE("f8" == std::format("{}", square::f8));

    REQUIRE("g1" == std::format("{}", square::g1));
    REQUIRE("g2" == std::format("{}", square::g2));
    REQUIRE("g3" == std::format("{}", square::g3));
    REQUIRE("g4" == std::format("{}", square::g4));
    REQUIRE("g5" == std::format("{}", square::g5));
    REQUIRE("g6" == std::format("{}", square::g6));
    REQUIRE("g7" == std::format("{}", square::g7));
    REQUIRE("g8" == std::format("{}", square::g8));

    REQUIRE("h1" == std::format("{}", square::h1));
    REQUIRE("h2" == std::format("{}", square::h2));
    REQUIRE("h3" == std::format("{}", square::h3));
    REQUIRE("h4" == std::format("{}", square::h4));
    REQUIRE("h5" == std::format("{}", square::h5));
    REQUIRE("h6" == std::format("{}", square::h6));
    REQUIRE("h7" == std::format("{}", square::h7));
    REQUIRE("h8" == std::format("{}", square::h8));
}
