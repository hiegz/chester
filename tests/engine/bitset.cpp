// clang-format off

#include <string>

#include <chester/engine/bitset.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using chester::engine::bitset;
using chester::engine::square;

TEST_CASE("chester::engine::bitset::empty()", "[engine][bitset]") {
    REQUIRE(0LL == bitset::empty().raw);
}

TEST_CASE("chester::engine::bitset::universal()", "[engine][bitset]") {
    REQUIRE(~0UL == bitset::universal().raw);
}

TEST_CASE("chester::engine::bitset::single()", "[engine][bitset]") {
    WHEN("bitset is empty") {
        const bitset bitset = bitset::empty();
        CAPTURE(bitset);
        REQUIRE(not bitset.single());
    }

    WHEN("bitset is single") {
        const square square = (enum square::value)GENERATE(range(0, 63));
        const bitset bitset = square;
        CAPTURE(bitset);
        REQUIRE(bitset.single());
    }

    WHEN("bitset has two elements") {
        const square square_i = (enum square::value)GENERATE(range(0, 63));
        const square square_j = (enum square::value)GENERATE(range(0, 63));

        if (square_i == square_j) {
            return;
        }

        const bitset bitset = square_i | square_j;

        CAPTURE(bitset);

        REQUIRE(not bitset.single());
    }

    WHEN("bitset is universal") {
        const bitset bitset = bitset::universal();
        CAPTURE(bitset);
        REQUIRE(not bitset.single());
    }
}

TEST_CASE("chester::engine::bitset::cardinality()", "[engine][bitset]") {
    WHEN("bitset is empty") {
        const bitset bitset = bitset::empty();
        CAPTURE(bitset);
        REQUIRE(0 == bitset.cardinality());
    }

    WHEN("bitset is single") {
        const square square = (enum square::value)GENERATE(range(0, 63));
        const bitset bitset = square;
        CAPTURE(bitset);
        REQUIRE(1 == bitset.cardinality());
    }

    WHEN("bitset has two elements") {
        const square square_i = (enum square::value)GENERATE(range(0, 63));
        const square square_j = (enum square::value)GENERATE(range(0, 63));

        if (square_i == square_j) {
            return;
        }

        const bitset bitset = square_i | square_j;

        CAPTURE(bitset);

        REQUIRE(2 == bitset.cardinality());
    }

    WHEN("bitset is universal") {
        const bitset bitset = bitset::universal();
        CAPTURE(bitset);
        REQUIRE(64 == bitset.cardinality());
    }
}

TEST_CASE("chester::engine::bitset::pop_front()", "[engine][bitset]") {
    WHEN("bitset is single") {
        const square square = (enum square::value)GENERATE(range(0, 63));
        bitset bitset = square;

        CAPTURE(bitset);

        REQUIRE(square == bitset.pop_front());
        REQUIRE(bitset == bitset::empty());
    }

    WHEN("bitset is universal") {
        bitset bitset = bitset::universal();

        CAPTURE(bitset);

        REQUIRE(square::a1 == bitset.pop_front());
        REQUIRE(63 == bitset.cardinality());
    }
}

TEST_CASE("chester::engine::bitset::pop_back()", "[engine][bitset]") {
    WHEN("bitset is single") {
        const auto square = (enum square::value)GENERATE(range(0, 63));
        bitset bitset = square;

        CAPTURE(bitset);

        REQUIRE(square == bitset.pop_back());
        REQUIRE(bitset == bitset::empty());
    }

    WHEN("bitset is universal") {
        bitset bitset = bitset::universal();

        INFO("bitset:\n" << bitset);

        REQUIRE(square::h8 == bitset.pop_back());
        REQUIRE(63 == bitset.cardinality());
    }
}

TEST_CASE("std::to_string(chester::engine::bitset)", "[engine][bitset][fmt]") {
    WHEN("bitset is empty") {
        constexpr auto expected =
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .";

        const auto found = std::to_string(bitset::empty());

        INFO("expected:\n" << expected);
        INFO("");
        INFO("found:\n" << found);

        REQUIRE((found == expected));
    }

    WHEN("bitset is universal") {
        constexpr auto expected =
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1\n"
            "1 1 1 1 1 1 1 1";

        const auto found = std::to_string(bitset::universal());

        INFO("expected:\n" << expected);
        INFO("");
        INFO("found:\n" << found);

        REQUIRE((found == expected));
    }
}
