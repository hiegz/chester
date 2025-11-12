// clang-format off

#include <string>

#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>

#include <catch2/catch_test_macros.hpp>

using chester::engine::piece;
using chester::engine::side;

TEST_CASE("chester::engine::piece operator << overload for std::ostream", "[engine][piece][fmt]") {
    REQUIRE("white king"   == std::to_string(side::white + piece::king));
    REQUIRE("white queen"  == std::to_string(side::white + piece::queen));
    REQUIRE("white rook"   == std::to_string(side::white + piece::rook));
    REQUIRE("white bishop" == std::to_string(side::white + piece::bishop));
    REQUIRE("white knight" == std::to_string(side::white + piece::knight));
    REQUIRE("white pawn"   == std::to_string(side::white + piece::pawn));

    REQUIRE("black king"   == std::to_string(side::black + piece::king));
    REQUIRE("black queen"  == std::to_string(side::black + piece::queen));
    REQUIRE("black rook"   == std::to_string(side::black + piece::rook));
    REQUIRE("black bishop" == std::to_string(side::black + piece::bishop));
    REQUIRE("black knight" == std::to_string(side::black + piece::knight));
    REQUIRE("black pawn"   == std::to_string(side::black + piece::pawn));
}
