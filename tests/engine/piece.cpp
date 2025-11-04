// clang-format off

#include <format>
#include <sstream>

#include <chester/engine/piece.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

using chester::engine::piece;

TEST_CASE("chester::engine::piece::value operator << overload for std::ostream", "[engine][piece::value][fmt]") {
    std::ostringstream ostr;

    SECTION("king") {
        const enum piece::value piece = piece::king;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("king" == ostr.str());
    }

    SECTION("queen") {
        const enum piece::value piece = piece::queen;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("queen" == ostr.str());
    }

    SECTION("rook") {
        const enum piece::value piece = piece::rook;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("rook" == ostr.str());
    }

    SECTION("bishop") {
        const enum piece::value piece = piece::bishop;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("bishop" == ostr.str());
    }

    SECTION("knight") {
        const enum piece::value piece = piece::knight;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("knight" == ostr.str());
    }

    SECTION("pawn") {
        const enum piece::value piece = piece::pawn;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("pawn" == ostr.str());
    }
}

TEST_CASE("chester::engine::piece operator << overload for std::ostream", "[engine][piece][fmt]") {
    std::ostringstream ostr;

    SECTION("king") {
        const piece piece = piece::king;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("king" == ostr.str());
    }

    SECTION("queen") {
        const piece piece = piece::queen;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("queen" == ostr.str());
    }

    SECTION("rook") {
        const piece piece = piece::rook;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("rook" == ostr.str());
    }

    SECTION("bishop") {
        const piece piece = piece::bishop;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("bishop" == ostr.str());
    }

    SECTION("knight") {
        const piece piece = piece::knight;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("knight" == ostr.str());
    }

    SECTION("pawn") {
        const piece piece = piece::pawn;
        CAPTURE(piece);
        ostr << piece;
        REQUIRE("pawn" == ostr.str());
    }
}
