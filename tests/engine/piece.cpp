// clang-format off

#include <format>
#include <sstream>

#include <chester/engine/piece.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

using chester::engine::piece;

TEST_CASE("chester::engine::piece::value formatter", "[engine][piece::value][fmt]") {
    REQUIRE("king"   == std::format("{}", piece::king));
    REQUIRE("queen"  == std::format("{}", piece::queen));
    REQUIRE("rook"   == std::format("{}", piece::rook));
    REQUIRE("bishop" == std::format("{}", piece::bishop));
    REQUIRE("knight" == std::format("{}", piece::knight));
    REQUIRE("pawn"   == std::format("{}", piece::pawn));
}

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

TEST_CASE("chester::engine::piece formatter", "[engine][piece][fmt]") {
    REQUIRE("king"   == std::format("{}", (piece)piece::king));
    REQUIRE("queen"  == std::format("{}", (piece)piece::queen));
    REQUIRE("rook"   == std::format("{}", (piece)piece::rook));
    REQUIRE("bishop" == std::format("{}", (piece)piece::bishop));
    REQUIRE("knight" == std::format("{}", (piece)piece::knight));
    REQUIRE("pawn"   == std::format("{}", (piece)piece::pawn));
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
