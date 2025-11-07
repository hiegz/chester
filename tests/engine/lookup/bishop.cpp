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

TEST_CASE("chester::engine::lookup<piece::bishop>()", "[.][engine][lookup][bishop]") {
    square   square;
    bitboard blockers;
    bitboard expected;

    std::tie(square, blockers, expected) =
        GENERATE(table<class square, bitboard, bitboard>({
            std::make_tuple(
                square::a1,
                bitboard::empty(),
                square::b2 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8),

            std::make_tuple(
                square::a1,
                square::h8,
                square::b2 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8),

            std::make_tuple(
                square::a1,
                square::g7,
                square::b2 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7),

            std::make_tuple(
                square::a1,
                square::d4,
                square::b2 |
                square::c3 |
                square::d4),

            std::make_tuple(
                square::a1,
                square::b2,
                square::b2),

            std::make_tuple(
                square::b2,
                bitboard::empty(),
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::a3,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::a1,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::c1,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::f3,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::a3,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::a1,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::c1,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::f3,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::a1 |
                square::a3 |
                square::c1 |
                square::f3,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::h8,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::h8 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::g7,
                square::a1 |
                square::c3 |
                square::d4 |
                square::e5 |
                square::f6 |
                square::g7 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::b2,
                square::d4,
                square::a1 |
                square::c3 |
                square::d4 |
                square::a3 |
                square::c1),

            std::make_tuple(
                square::e3,
                bitboard::empty(),
                square::c1 |
                square::d2 |
                square::g1 |
                square::f2 |
                square::f4 |
                square::g5 |
                square::h6 |
                square::d4 |
                square::c5 |
                square::b6 |
                square::a7),

            std::make_tuple(
                square::e3,
                square::c5,
                square::c1 |
                square::d2 |
                square::g1 |
                square::f2 |
                square::f4 |
                square::g5 |
                square::h6 |
                square::d4 |
                square::c5),

            std::make_tuple(
                square::h8,
                square::c3,
                square::g7 |
                square::f6 |
                square::e5 |
                square::d4 |
                square::c3),
        }));

    const bitboard found = chester::engine::lookup<piece::bishop>(square, blockers);

    INFO("square: " << square);
    INFO("");
    INFO("blockers:\n" << blockers);
    INFO("");
    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found << "\n\n");

    REQUIRE((expected == found));
}
