#include <tuple>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::bitboard;
using chester::engine::square;

TEST_CASE("chester::engine::lookup::in_between()",
          "[chester][engine][in_between]") {
    square   a;
    square   b;
    bitboard expected;

    std::tie(a, b, expected) = GENERATE(table<square, square, bitboard>({
        std::make_tuple(square::a1, square::a1, bitboard::empty()),
        std::make_tuple(square::h1, square::h1, bitboard::empty()),
        std::make_tuple(square::a8, square::a8, bitboard::empty()),
        std::make_tuple(square::h8, square::h8, bitboard::empty()),

        std::make_tuple(square::d4, square::d4, bitboard::empty()),
        std::make_tuple(square::e4, square::e4, bitboard::empty()),
        std::make_tuple(square::d5, square::d5, bitboard::empty()),
        std::make_tuple(square::e5, square::e5, bitboard::empty()),

        std::make_tuple(square::d4, square::d5, bitboard::empty()),
        std::make_tuple(square::d5, square::d4, bitboard::empty()),
        std::make_tuple(square::e4, square::e5, bitboard::empty()),
        std::make_tuple(square::e5, square::e4, bitboard::empty()),
        std::make_tuple(square::d4, square::e4, bitboard::empty()),
        std::make_tuple(square::e4, square::d4, bitboard::empty()),
        std::make_tuple(square::d5, square::e5, bitboard::empty()),
        std::make_tuple(square::e5, square::d5, bitboard::empty()),
        std::make_tuple(square::d4, square::e5, bitboard::empty()),
        std::make_tuple(square::e5, square::d4, bitboard::empty()),
        std::make_tuple(square::d5, square::e4, bitboard::empty()),
        std::make_tuple(square::e4, square::d5, bitboard::empty()),

        std::make_tuple(square::d3, square::d6, square::d4 | square::d5),
        std::make_tuple(square::d6, square::d3, square::d4 | square::d5),
        std::make_tuple(square::e3, square::e6, square::e4 | square::e5),
        std::make_tuple(square::e6, square::e3, square::e4 | square::e5),
        std::make_tuple(square::c4, square::f4, square::d4 | square::e4),
        std::make_tuple(square::f4, square::c4, square::d4 | square::e4),
        std::make_tuple(square::c5, square::f5, square::d5 | square::e5),
        std::make_tuple(square::f5, square::c5, square::d5 | square::e5),
        std::make_tuple(square::c3, square::f6, square::d4 | square::e5),
        std::make_tuple(square::f6, square::c3, square::d4 | square::e5),
        std::make_tuple(square::c6, square::f3, square::d5 | square::e4),
        std::make_tuple(square::f3, square::c6, square::d5 | square::e4),
    }));

    const bitboard found = chester::engine::lookup::in_between(a, b);

    INFO("squares:\n" << (a | b));
    INFO("");
    INFO("expected bitboard:\n" << expected);
    INFO("");
    INFO("found bitboard:\n" << found);

    REQUIRE((found == expected));
}
