#include <string>

#include <chester/castling.hpp>

#include <catch2/catch_test_macros.hpp>

using chester::castling;

// clang-format off

TEST_CASE("chester::castling operations", "[engine][castling]") {
    const castling c = castling::none | castling::white_kingside | castling::black_queenside;

    REQUIRE(castling::none == ~castling::all);
    REQUIRE(castling::all  == ~castling::none);

    REQUIRE(castling::none == (c & castling::black_kingside));
    REQUIRE(castling::none == (c & castling::white_queenside));
    REQUIRE(castling::none != (c & castling::black_queenside));
    REQUIRE(castling::none != (c & castling::white_kingside));
}

TEST_CASE("chester::castling string representation",
          "[engine][castling][fmt]") {
    REQUIRE("" == std::to_string(castling::none)); // NOLINT
    REQUIRE("white kingside, white queenside, black kingside, black queenside" == std::to_string(castling::all));
    REQUIRE("white queenside, black kingside, black queenside" == std::to_string(castling::all ^ castling::white_kingside));
    REQUIRE("white kingside, white queenside, black kingside" == std::to_string(castling::all ^ castling::black_queenside));
    REQUIRE("white kingside, black queenside" == std::to_string(castling::all ^ castling::white_queenside ^ castling::black_kingside));
}
