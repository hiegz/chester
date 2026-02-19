#include <catch2/catch_test_macros.hpp>

#include <chester/move.hpp>
#include <chester/move_type.hpp>
#include <chester/piece_type.hpp>
#include <chester/square.hpp>

#include <string>

using chester::move;
using chester::move_type;
using chester::piece_type;
using chester::square;

// clang-format off

TEST_CASE("std::to_string(chester::move)", "[engine][move][fmt]") {
    REQUIRE("a1 -> a3" == std::to_string(move(square::a1, square::a3, move_type::normal)));
    REQUIRE("h7 -> h8 (promotion to knight)" == std::to_string(move(square::h7, square::h8, move_type::promotion, piece_type::knight)));
    REQUIRE("e1 -> g1 (castling)" == std::to_string(move(square::e1, square::g1, move_type::castling)));
    REQUIRE("d5 -> c6 (en passant)" == std::to_string(move(square::d5, square::c6, move_type::enpassant)));
}
