// clang-format off

#include <vector>
#include <sstream>

#include <chester/engine/square.hpp>
#include <chester/engine/bitboard.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

using chester::engine::bitboard;
using chester::engine::square;

TEST_CASE("chester::engine::bitboard operator << overload for std::ostream",
          "[engine][bitboard][fmt]") {
    std::ostringstream ss;

    WHEN("bitboard is empty") {
        ss << bitboard::empty();

        const     auto actual   = ss.str();
        constexpr auto expected =
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .";

        INFO("actual:\n" << actual << "\n\n");
        INFO("expected:\n" << expected << "\n");

        const bool eq = (actual == expected);

        REQUIRE(eq);
    }

    WHEN("bitboard is non-empty") {
        ss << (square::a1 | square::h8 | square::f5);

        const     auto actual   = ss.str();
        constexpr auto expected =
            ". . . . . . . 1\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . 1 . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            "1 . . . . . . .";

        INFO("actual:\n" << actual << "\n\n");
        INFO("expected:\n" << expected << "\n");

        const bool eq = (actual == expected);

        REQUIRE(eq);
    }

    WHEN("bitboard universal") {
        ss << bitboard::universal();

        const     auto actual   = ss.str();
        constexpr auto expected =
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1";

        INFO("actual:\n" << actual << "\n\n");
        INFO("expected:\n" << expected << "\n");

        const bool eq = (actual == expected);

        REQUIRE(eq);
    }

    WHEN("bitboard non-universal") {
        ss << (bitboard::universal() ^ square::b6 ^ square::h1);

        const     auto actual   = ss.str();
        constexpr auto expected =
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 . 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 .";

        INFO("actual:\n" << actual << "\n\n");
        INFO("expected:\n" << expected << "\n");

        const bool eq = (actual == expected);

        REQUIRE(eq);
    }
}

TEST_CASE("chester::engine::bitboard::is_empty()", "[engine][bitboard]") {
    WHEN("bitboard is empty") {
        const auto bitboard = bitboard::empty();
        const auto expected = true;
        const auto actual   = bitboard.is_empty();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is not empty") {
        const auto bitboard = (class bitboard)square::a1;
        const auto expected = false;
        const auto actual   = bitboard.is_empty();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is universal") {
        const auto bitboard = bitboard::universal();
        const auto expected = false;
        const auto actual   = bitboard.is_empty();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }
}

TEST_CASE("chester::engine::bitboard::is_universal()", "[engine][bitboard]") {
    WHEN("bitboard is empty") {
        const auto bitboard = bitboard::empty();
        const auto expected = false;
        const auto actual   = bitboard.is_universal();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is not universal") {
        const auto bitboard = bitboard::universal() ^ square::a1;
        const auto expected = false;
        const auto actual   = bitboard.is_universal();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is universal") {
        const auto bitboard = bitboard::universal();
        const auto expected = true;
        const auto actual   = bitboard.is_universal();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }
}

TEST_CASE("chester::engine::bitboard::is_single()", "[engine][bitboard]") {
    WHEN("bitboard is empty") {
        const auto bitboard = bitboard::empty();
        const auto expected = false;
        const auto actual   = bitboard.is_single();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is single") {
        const auto bitboard = (class bitboard)square::e3;
        const auto expected = true;
        const auto actual   = bitboard.is_single();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is not single") {
        const auto bitboard = square::e3 | square::h1;
        const auto expected = false;
        const auto actual   = bitboard.is_single();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is universal") {
        const auto bitboard = bitboard::universal();
        const auto expected = false;
        const auto actual   = bitboard.is_single();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected: " << (expected ? "true" : "false"));
        INFO("found:    " << (actual   ? "true" : "false"));

        REQUIRE(expected == actual);
    }
}

TEST_CASE("chester::engine::bitboard::cardinality()", "[engine][bitboard]") {
    WHEN("bitboard is empty") {
        const auto bitboard = bitboard::empty();
        const auto expected = 0;
        const auto actual   = bitboard.cardinality();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected cardinality: " << expected);
        INFO("found cardinality:    " << actual);

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is single") {
        const auto bitboard = (class bitboard)square::d7;
        const auto expected = 1;
        const auto actual   = bitboard.cardinality();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected cardinality: " << expected);
        INFO("found cardinality:    " << actual);

        REQUIRE(expected == actual);
    }

    WHEN("bitboard with two squares") {
        const auto bitboard = square::d7 | square::h8;
        const auto expected = 2;
        const auto actual   = bitboard.cardinality();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected cardinality: " << expected);
        INFO("found cardinality:    " << actual);

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is almost universal") {
        const auto bitboard = bitboard::universal() ^ square::f4;
        const auto expected = 63;
        const auto actual   = bitboard.cardinality();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected cardinality: " << expected);
        INFO("found cardinality:    " << actual);

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is universal") {
        const auto bitboard = bitboard::universal();
        const auto expected = 64;
        const auto actual   = bitboard.cardinality();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected cardinality: " << expected);
        INFO("found cardinality:    " << actual);

        REQUIRE(expected == actual);
    }
}

TEST_CASE("chester::engine::bitboard::pop_front()", "[engine][bitboard]") {
    WHEN("bitboard is single") {
        const auto original_bitboard = (class bitboard)square::d5;
        const auto expected_bitboard = bitboard::empty();
        const auto expected_square   = square::d5;
              auto actual_bitboard   = original_bitboard;
        const auto actual_square     = actual_bitboard.pop_front();

        INFO("original bitboard\n" << original_bitboard << "\n\n");
        INFO("expected bitboard\n" << expected_bitboard << "\n\n");
        INFO("actual bitboard\n"   << actual_bitboard   << "\n\n");
        INFO("expected square: "   << expected_square);
        INFO("actual square:   "   << actual_square);

        REQUIRE(expected_bitboard == actual_bitboard);
        REQUIRE(expected_square   == actual_square);
    }

    WHEN("bitboard has to squares set") {
        const auto original_bitboard = square::a3 | square::b2;
        const auto expected_bitboard = (class bitboard)square::a3;
        const auto expected_square   = square::b2;
              auto actual_bitboard   = original_bitboard;
        const auto actual_square     = actual_bitboard.pop_front();

        INFO("original bitboard\n" << original_bitboard << "\n\n");
        INFO("expected bitboard\n" << expected_bitboard << "\n\n");
        INFO("actual bitboard\n"   << actual_bitboard   << "\n\n");
        INFO("expected square: "   << expected_square);
        INFO("actual square:   "   << actual_square);

        REQUIRE(expected_bitboard == actual_bitboard);
        REQUIRE(expected_square   == actual_square);
    }

    WHEN("bitboard is universal") {
        const auto original_bitboard = bitboard::universal();
        const auto expected_bitboard = bitboard::universal() ^ square::a1;
        const auto expected_square   = square::a1;
              auto actual_bitboard   = original_bitboard;
        const auto actual_square     = actual_bitboard.pop_front();

        INFO("original bitboard\n" << original_bitboard << "\n\n");
        INFO("expected bitboard\n" << expected_bitboard << "\n\n");
        INFO("actual bitboard\n"   << actual_bitboard   << "\n\n");
        INFO("expected square: "   << expected_square);
        INFO("actual square:   "   << actual_square);

        REQUIRE(expected_bitboard == actual_bitboard);
        REQUIRE(expected_square   == actual_square);
    }
}

TEST_CASE("chester::engine::bitboard::pop_back()", "[engine][bitboard]") {
    WHEN("bitboard is single") {
        const auto original_bitboard = (class bitboard)square::d5;
        const auto expected_bitboard = bitboard::empty();
        const auto expected_square   = square::d5;
              auto actual_bitboard   = original_bitboard;
        const auto actual_square     = actual_bitboard.pop_back();

        INFO("original bitboard\n" << original_bitboard << "\n\n");
        INFO("expected bitboard\n" << expected_bitboard << "\n\n");
        INFO("actual bitboard\n"   << actual_bitboard   << "\n\n");
        INFO("expected square: "   << expected_square);
        INFO("actual square:   "   << actual_square);

        REQUIRE(expected_bitboard == actual_bitboard);
        REQUIRE(expected_square   == actual_square);
    }

    WHEN("bitboard has to squares set") {
        const auto original_bitboard = square::a3 | square::b2;
        const auto expected_bitboard = (class bitboard)square::b2;
        const auto expected_square   = square::a3;
              auto actual_bitboard   = original_bitboard;
        const auto actual_square     = actual_bitboard.pop_back();

        INFO("original bitboard\n" << original_bitboard << "\n\n");
        INFO("expected bitboard\n" << expected_bitboard << "\n\n");
        INFO("actual bitboard\n"   << actual_bitboard   << "\n\n");
        INFO("expected square: "   << expected_square);
        INFO("actual square:   "   << actual_square);

        REQUIRE(expected_bitboard == actual_bitboard);
        REQUIRE(expected_square   == actual_square);
    }

    WHEN("bitboard is universal") {
        const auto original_bitboard = bitboard::universal();
        const auto expected_bitboard = bitboard::universal() ^ square::h8;
        const auto expected_square   = square::h8;
              auto actual_bitboard   = original_bitboard;
        const auto actual_square     = actual_bitboard.pop_back();

        INFO("original bitboard\n" << original_bitboard << "\n\n");
        INFO("expected bitboard\n" << expected_bitboard << "\n\n");
        INFO("actual bitboard\n"   << actual_bitboard   << "\n\n");
        INFO("expected square: "   << expected_square);
        INFO("actual square:   "   << actual_square);

        REQUIRE(expected_bitboard == actual_bitboard);
        REQUIRE(expected_square   == actual_square);
    }
}

TEST_CASE("chester::engine::bitboard::powerset", "[engine][bitboard]") {
    WHEN("bitboard is empty") {
        const auto bitboard = bitboard::empty();
        const auto expected = std::vector<class bitboard>{bitboard::empty()};
        const auto actual   = bitboard.powerset();

        INFO("bitboard\n" << bitboard << "\n\n");
        INFO("expected bitboards\n");
        for (const auto item : expected) {
            INFO(item);
        }
        INFO("\n\n");

        INFO("actual bitboards\n");
        for (const auto item : actual) {
            INFO(item);
        }
        INFO("\n\n");

        REQUIRE(expected == actual);
    }

    WHEN("bitboard is single") {
        const auto bitboard = bitboard::empty() | square::d2;
        const auto expected = std::vector<class bitboard>{bitboard::empty(), square::d2};
        const auto actual   = bitboard.powerset();

        REQUIRE(expected == actual);
    }

    WHEN("bitboard has two elements") {
        const auto bitboard = bitboard::empty() | square::d2 | square::h8;
        const auto expected = std::vector<class bitboard>{bitboard::empty(), square::d2, square::h8, square::d2 | square::h8};
        const auto actual   = bitboard.powerset();

        REQUIRE(expected == actual);
    }
}
