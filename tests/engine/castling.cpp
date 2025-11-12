#include <string>

#include <chester/engine/castling.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>

#include <catch2/catch_test_macros.hpp>

using chester::engine::castling;
using chester::engine::piece;
using chester::engine::side;

// clang-format off

TEST_CASE("chester::engine::castling operations", "[engine][castling]") {
    const castling c = castling::none() | (side::white + piece::king) |
                       (side::black + piece::queen);

    REQUIRE(castling::none() == ~castling::all());
    REQUIRE(castling::all()  == ~castling::none());

    REQUIRE(castling::none() == (c & (side::black + piece::king)));
    REQUIRE(castling::none() == (c & (side::white + piece::queen)));
    REQUIRE(castling::none() != (c & (side::black + piece::queen)));
    REQUIRE(castling::none() != (c & (side::white + piece::king)));
}

TEST_CASE("chester::engine::castling string representation",
          "[engine][castling][fmt]") {
    REQUIRE("" == std::to_string(castling::none())); // NOLINT
    REQUIRE("white kingside, white queenside, black kingside, black queenside" == std::to_string(castling::all()));
    REQUIRE("white queenside, black kingside, black queenside" == std::to_string(castling::all() ^ (side::white + piece::king)));
    REQUIRE("white kingside, white queenside, black kingside" == std::to_string(castling::all() ^ (side::black + piece::queen)));
    REQUIRE("white kingside, black queenside" == std::to_string(castling::all() ^ (side::white + piece::queen) ^ (side::black + piece::king)));
}
