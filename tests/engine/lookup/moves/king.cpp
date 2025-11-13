// clang-format off

#include <tuple>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_message.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::bitboard;
using chester::engine::square;
using chester::engine::piece;

TEST_CASE("chester::engine::lookup::moves<chester::engine::piece::king>()",
          "[.][engine][lookup][king]") {
    square   square;
    bitboard expected;

    std::tie(square, expected) =
        GENERATE(table<class square, class bitboard>({
            // 1st rank
            std::make_tuple(square::a1, square::b1 | square::a2 | square::b2),
            std::make_tuple(square::b1, square::a1 | square::c1 | square::a2 | square::b2 | square::c2),
            std::make_tuple(square::d1, square::c1 | square::e1 | square::c2 | square::d2 | square::e2),
            std::make_tuple(square::e1, square::d1 | square::f1 | square::d2 | square::e2 | square::f2),
            std::make_tuple(square::g1, square::f1 | square::h1 | square::f2 | square::g2 | square::h2),
            std::make_tuple(square::h1, square::g1 | square::h2 | square::g2),

            // 4th rank
            std::make_tuple(square::a4, square::b4 | square::a3 | square::b3 | square::a5 | square::b5),
            std::make_tuple(square::b4, square::a4 | square::c4 | square::a3 | square::b3 | square::c3 | square::a5 | square::b5 | square::c5),
            std::make_tuple(square::d4, square::c4 | square::e4 | square::c3 | square::d3 | square::e3 | square::c5 | square::d5 | square::e5),
            std::make_tuple(square::e4, square::d4 | square::f4 | square::d3 | square::e3 | square::f3 | square::d5 | square::e5 | square::f5),
            std::make_tuple(square::g4, square::f4 | square::h4 | square::f3 | square::g3 | square::h3 | square::f5 | square::g5 | square::h5),
            std::make_tuple(square::h4, square::g4 | square::g3 | square::h3 | square::g5 | square::h5),

            // 5th rank
            std::make_tuple(square::a5, square::b5 | square::a4 | square::b4 | square::a6 | square::b6),
            std::make_tuple(square::b5, square::a5 | square::c5 | square::a4 | square::b4 | square::c4 | square::a6 | square::b6 | square::c6),
            std::make_tuple(square::d5, square::c5 | square::e5 | square::c4 | square::d4 | square::e4 | square::c6 | square::d6 | square::e6),
            std::make_tuple(square::e5, square::d5 | square::f5 | square::d4 | square::e4 | square::f4 | square::d6 | square::e6 | square::f6),
            std::make_tuple(square::g5, square::f5 | square::h5 | square::f4 | square::g4 | square::h4 | square::f6 | square::g6 | square::h6),
            std::make_tuple(square::h5, square::g5 | square::g4 | square::h4 | square::g6 | square::h6),

            // 8th rank
            std::make_tuple(square::a8, square::b8 | square::a7 | square::b7),
            std::make_tuple(square::b8, square::a8 | square::c8 | square::a7 | square::b7 | square::c7),
            std::make_tuple(square::d8, square::c8 | square::e8 | square::c7 | square::d7 | square::e7),
            std::make_tuple(square::e8, square::d8 | square::f8 | square::d7 | square::e7 | square::f7),
            std::make_tuple(square::g8, square::f8 | square::h8 | square::f7 | square::g7 | square::h7),
            std::make_tuple(square::h8, square::g8 | square::h7 | square::g7),
        }));

    const bitboard found = chester::engine::lookup::moves<piece::king>(square);

    INFO("square: " << square);
    INFO("");
    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found << "\n\n");

    REQUIRE((expected == found));
}
