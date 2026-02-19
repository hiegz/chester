// clang-format off

#include <string>

#include <chester/piece.hpp>

#include <catch2/catch_test_macros.hpp>

using chester::piece;

TEST_CASE("chester::piece operator << overload for std::ostream", "[engine][piece][fmt]") {
    REQUIRE("white king"   == std::to_string(piece::white_king));
    REQUIRE("white queen"  == std::to_string(piece::white_queen));
    REQUIRE("white rook"   == std::to_string(piece::white_rook));
    REQUIRE("white bishop" == std::to_string(piece::white_bishop));
    REQUIRE("white knight" == std::to_string(piece::white_knight));
    REQUIRE("white pawn"   == std::to_string(piece::white_pawn));

    REQUIRE("black king"   == std::to_string(piece::black_king));
    REQUIRE("black queen"  == std::to_string(piece::black_queen));
    REQUIRE("black rook"   == std::to_string(piece::black_rook));
    REQUIRE("black bishop" == std::to_string(piece::black_bishop));
    REQUIRE("black knight" == std::to_string(piece::black_knight));
    REQUIRE("black pawn"   == std::to_string(piece::black_pawn));
}
