// clang-format off

#include <tuple>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::bitboard;
using chester::engine::piece;
using chester::engine::square;

TEST_CASE("chester::engine::lookup<piece::rook>()", "[.][engine][lookup][rook]") {
    square   square;
    bitboard blockers;
    bitboard expected;

    std::tie(square, blockers, expected) =
        GENERATE(table<class square, bitboard, bitboard>({
            std::make_tuple(
                square::a8,
                bitboard::empty(),
                square::a1 |
                square::a2 |
                square::a3 |
                square::a4 |
                square::a5 |
                square::a6 |
                square::a7 |
                square::b8 |
                square::c8 |
                square::d8 |
                square::e8 |
                square::f8 |
                square::g8 |
                square::h8),

            std::make_tuple(
                square::a8,
                square::c8 | square::a4,
                square::a4 |
                square::a5 |
                square::a6 |
                square::a7 |
                square::b8 |
                square::c8),

            std::make_tuple(
                square::h1,
                bitboard::empty(),
                square::h2 |
                square::h3 |
                square::h4 |
                square::h5 |
                square::h6 |
                square::h7 |
                square::h8 |
                square::g1 |
                square::f1 |
                square::e1 |
                square::d1 |
                square::c1 |
                square::b1 |
                square::a1),

            std::make_tuple(
                square::h1,
                square::e1 | square::h5,
                square::h2 |
                square::h3 |
                square::h4 |
                square::h5 |
                square::g1 |
                square::f1 |
                square::e1),

            std::make_tuple(
                square::e4,
                square::a1 |
                square::h8 |
                square::f6 |
                square::e2 |
                square::e7 |
                square::b4,
                square::e2 |
                square::e3 |
                square::e5 |
                square::e6 |
                square::e7 |
                square::b4 |
                square::c4 |
                square::d4 |
                square::f4 |
                square::g4 |
                square::h4),
        }));

    const bitboard found = chester::engine::lookup<piece::rook>(square, blockers);

    INFO("square: " << square);
    INFO("");
    INFO("blockers:\n" << blockers);
    INFO("");
    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found << "\n\n");

    REQUIRE((expected == found));
}
