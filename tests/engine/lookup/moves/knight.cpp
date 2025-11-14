// clang-format off

#include <tuple>

#include <chester/engine/bitset.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_message.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::bitset;
using chester::engine::square;
using chester::engine::piece;

TEST_CASE("chester::engine::lookup::moves<chester::engine::piece::knight>()",
          "[.][engine][lookup][knight]") {
    square   square;
    bitset expected;

    std::tie(square, expected) =
        GENERATE(table<class square, class bitset>({
            // top-left edge
            std::make_tuple(square::a8, square::b6 | square::c7),
            std::make_tuple(square::b8, square::a6 | square::c6 | square::d7),
            std::make_tuple(square::c8, square::a7 | square::b6 | square::d6 | square::e7),
            std::make_tuple(square::a7, square::b5 | square::c6 | square::c8),
            std::make_tuple(square::b7, square::a5 | square::c5 | square::d6 | square::d8),
            std::make_tuple(square::c7, square::a8 | square::a6 | square::b5 | square::d5 | square::e6 | square::e8),
            std::make_tuple(square::a6, square::b4 | square::c5 | square::c7 | square::b8),
            std::make_tuple(square::b6, square::a8 | square::a4 | square::c4 | square::d5 | square::d7 | square::c8),
            std::make_tuple(square::c6, square::a7 | square::a5 | square::b4 | square::d4 | square::e5 | square::e7 | square::d8 | square::b8),

            // top-right edge
            std::make_tuple(square::h8, square::g6 | square::f7),
            std::make_tuple(square::g8, square::h6 | square::f6 | square::e7),
            std::make_tuple(square::f8, square::h7 | square::g6 | square::e6 | square::d7),
            std::make_tuple(square::h7, square::g5 | square::f6 | square::f8),
            std::make_tuple(square::g7, square::h5 | square::f5 | square::e6 | square::e8),
            std::make_tuple(square::f7, square::h8 | square::h6 | square::g5 | square::e5 | square::d6 | square::d8),
            std::make_tuple(square::h6, square::g4 | square::f5 | square::f7 | square::g8),
            std::make_tuple(square::g6, square::h4 | square::f4 | square::e5 | square::e7 | square::f8 | square::h8),
            std::make_tuple(square::f6, square::h5 | square::g4 | square::e4 | square::d5 | square::d7 | square::e8 | square::g8 | square::h7),

            // bottom-right edge
            std::make_tuple(square::h1, square::g3 | square::f2),
            std::make_tuple(square::g1, square::h3 | square::f3 | square::e2),
            std::make_tuple(square::f1, square::h2 | square::g3 | square::e3 | square::d2),
            std::make_tuple(square::h2, square::g4 | square::f3 | square::f1),
            std::make_tuple(square::g2, square::h4 | square::f4 | square::e3 | square::e1),
            std::make_tuple(square::f2, square::h1 | square::h3 | square::g4 | square::e4 | square::d3 | square::d1),
            std::make_tuple(square::h3, square::g5 | square::f4 | square::f2 | square::g1),
            std::make_tuple(square::g3, square::h1 | square::h5 | square::f5 | square::e4 | square::e2 | square::f1),
            std::make_tuple(square::f3, square::g1 | square::h2 | square::h4 | square::g5 | square::e5 | square::d4 | square::d2 | square::e1),

            // bottom-left edge
            std::make_tuple(square::a1, square::b3 | square::c2),
            std::make_tuple(square::b1, square::a3 | square::c3 | square::d2),
            std::make_tuple(square::c1, square::a2 | square::b3 | square::d3 | square::e2),
            std::make_tuple(square::a2, square::b4 | square::c3 | square::c1),
            std::make_tuple(square::b2, square::a4 | square::c4 | square::d3 | square::d1),
            std::make_tuple(square::c2, square::a1 | square::a3 | square::b4 | square::d4 | square::e3 | square::e1),
            std::make_tuple(square::a3, square::b5 | square::c4 | square::c2 | square::b1),
            std::make_tuple(square::b3, square::a1 | square::a5 | square::c5 | square::d4 | square::d2 | square::c1),
            std::make_tuple(square::c3, square::b1 | square::a2 | square::a4 | square::b5 | square::d5 | square::e4 | square::e2 | square::d1),
        }));

    const bitset found = chester::engine::lookup::moves<piece::knight>(square);

    INFO("square: " << square);
    INFO("");
    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found << "\n\n");

    REQUIRE((expected == found));
}
