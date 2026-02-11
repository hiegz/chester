#include <catch2/catch_test_macros.hpp>

#include <chester/engine/move.hpp>
#include <chester/engine/move_type.hpp>
#include <chester/engine/piece_type.hpp>
#include <chester/engine/square.hpp>

#include <string>

using chester::engine::move;
using chester::engine::move_type;
using chester::engine::piece_type;
using chester::engine::square;

// clang-format off

TEST_CASE("std::to_string(chester::engine::move)", "[engine][move][fmt]") {
    REQUIRE("a1 -> a3" == std::to_string(move(square::a1, square::a3, move_type::normal)));
    REQUIRE("h7 -> h8 (promotion to knight)" == std::to_string(move(square::h7, square::h8, move_type::promotion, piece_type::knight)));
    REQUIRE("e1 -> g1 (castling)" == std::to_string(move(square::e1, square::g1, move_type::castling)));
    REQUIRE("d5 -> c6 (en passant)" == std::to_string(move(square::d5, square::c6, move_type::enpassant)));
}
