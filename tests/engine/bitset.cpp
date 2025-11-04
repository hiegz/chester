// clang-format off

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include <chester/engine/bitset.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>

TEST_CASE("chester::engine::bitset::empty()", "[engine][bitset]") {
    REQUIRE( 0LL == chester::engine::bitset::empty<std::uint64_t>());
}

TEST_CASE("chester::engine::bitset::universal()", "[engine][bitset]") {
    REQUIRE(~0UL == chester::engine::bitset::universal<std::uint64_t>());
}

TEST_CASE("chester::engine::bitset::is_empty()", "[engine][bitset]") {
    WHEN("bitset is empty") {
        const auto bitset = chester::engine::bitset::empty<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(chester::engine::bitset::is_empty(bitset));
    }

    WHEN("bitset is universal") {
        const auto bitset = chester::engine::bitset::universal<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(not chester::engine::bitset::is_empty(bitset));
    }

    WHEN("bitset is not empty") {
        const auto bitset = GENERATE(take(8, random(1UL, std::numeric_limits<std::uint64_t>::max())));
        CAPTURE(bitset);
        REQUIRE(not chester::engine::bitset::is_empty(bitset));
    }
}

TEST_CASE("chester::engine::bitset::is_universal()", "[engine][bitset]") {
    WHEN("bitset is universal") {
        const auto bitset = chester::engine::bitset::universal<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(chester::engine::bitset::is_universal(bitset));
    }

    WHEN("bitset is empty") {
        const auto bitset = chester::engine::bitset::empty<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(not chester::engine::bitset::is_universal(bitset));
    }

    WHEN("bitset is not universal") {
        const auto bitset = GENERATE(take(9, random(0UL, std::numeric_limits<std::uint64_t>::max() - 1)));
        CAPTURE(bitset);
        REQUIRE(not chester::engine::bitset::is_universal(bitset));
    }
}

TEST_CASE("chester::engine::bitset::is_single()", "[engine][bitset]") {
    WHEN("bitset is empty") {
        const auto bitset = chester::engine::bitset::empty<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(not chester::engine::bitset::is_single(bitset));
    }

    WHEN("bitset is single") {
        const auto square = GENERATE(range(0, 63));
        const auto bitset = 1UL << (std::size_t)square;
        CAPTURE(bitset);
        REQUIRE(chester::engine::bitset::is_single(bitset));
    }

    WHEN("bitset has two elements") {
        const auto square_i = GENERATE(range(0, 63));
        const auto square_j = GENERATE(range(0, 63));

        if (square_i == square_j) {
            return;
        }

        const auto bitset = (1UL << square_i) | (1UL << square_j); // NOLINT

        CAPTURE(bitset);

        REQUIRE(not chester::engine::bitset::is_single(bitset));
    }

    WHEN("bitset is universal") {
        const auto bitset = chester::engine::bitset::universal<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(not chester::engine::bitset::is_single(bitset));
    }
}

TEST_CASE("chester::engine::bitset::cardinality()", "[engine][bitset]") {
    WHEN("bitset is empty") {
        const auto bitset = chester::engine::bitset::empty<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(0 == chester::engine::bitset::cardinality(bitset));
    }

    WHEN("bitset is single") {
        const auto square = GENERATE(range(0, 63));
        const auto bitset = 1UL << square; // NOLINT
        CAPTURE(bitset);
        REQUIRE(1 == chester::engine::bitset::cardinality(bitset));
    }

    WHEN("bitset has two elements") {
        const auto square_i = GENERATE(range(0, 63));
        const auto square_j = GENERATE(range(0, 63));

        if (square_i == square_j) {
            return;
        }

        const auto bitset = (1UL << square_i) | (1UL << square_j); // NOLINT

        CAPTURE(bitset);

        REQUIRE(2 == chester::engine::bitset::cardinality(bitset));
    }

    WHEN("bitset is universal") {
        const auto bitset = chester::engine::bitset::universal<std::uint64_t>();
        CAPTURE(bitset);
        REQUIRE(64 == chester::engine::bitset::cardinality(bitset));
    }
}

TEST_CASE("chester::engine::bitset::pop_front()", "[engine][bitset]") {
    WHEN("bitset is single") {
        const auto square = GENERATE(range(0, 63));
        const auto index  = (std::uint64_t)square;
              auto bitset = 1UL << square; // NOLINT

        CAPTURE(bitset);
        CAPTURE(index);

        REQUIRE(index == chester::engine::bitset::pop_front(&bitset));
        REQUIRE(chester::engine::bitset::is_empty(bitset));
    }

    WHEN("bitset is universal") {
        const auto index  = 0UL;
              auto bitset = chester::engine::bitset::universal<std::uint64_t>();

        CAPTURE(bitset);
        CAPTURE(index);

        REQUIRE(index == chester::engine::bitset::pop_front(&bitset));
        REQUIRE(63    == chester::engine::bitset::cardinality(bitset));
    }
}

TEST_CASE("chester::engine::bitset::pop_back()", "[engine][bitset]") {
    WHEN("bitset is single") {
        const auto square = GENERATE(range(0, 63));
        const auto index  = (std::uint64_t)square;
              auto bitset = 1UL << square; // NOLINT

        CAPTURE(bitset);
        CAPTURE(index);

        REQUIRE(index == chester::engine::bitset::pop_back(&bitset));
        REQUIRE(chester::engine::bitset::is_empty(bitset));
    }

    WHEN("bitset is universal") {
        const auto index  = 63;
              auto bitset = chester::engine::bitset::universal<std::uint64_t>();

        CAPTURE(bitset);
        CAPTURE(index);

        REQUIRE(index == chester::engine::bitset::pop_back(&bitset));
        REQUIRE(63    == chester::engine::bitset::cardinality(bitset));
    }
}

TEST_CASE("chester::engine::bitset::powerset()", "[engine][bitset]") {
    WHEN("bitset is empty") {
        const auto bitset = chester::engine::bitset::empty<std::uint64_t>();
        const auto powerset = chester::engine::bitset::powerset(bitset);

        CAPTURE(bitset);
        CAPTURE(powerset);

        REQUIRE(1 == powerset.size());
        REQUIRE(chester::engine::bitset::is_empty(powerset[0]));
    }

    WHEN("bitset is single") {
        const auto square = GENERATE(range(0, 63));
        const auto bitset = 1UL << (std::size_t)square;
        const auto powerset = chester::engine::bitset::powerset(bitset);

        CAPTURE(bitset);
        CAPTURE(powerset);

        REQUIRE(2 == powerset.size());
        REQUIRE(std::ranges::find_if(powerset, [&](auto entry) -> auto { return entry == bitset; }) != powerset.end());
        REQUIRE(std::ranges::find_if(powerset, [&](auto entry) -> auto { return chester::engine::bitset::is_empty(entry); }) != powerset.end());
    }

    WHEN("bitset has two elements") {
        const auto square_i = GENERATE(1, 5, 50);
        const auto square_j = GENERATE(29, 7, 31);
        const auto bitset_i = 1UL << (std::size_t)square_i;
        const auto bitset_j = 1UL << (std::size_t)square_j;
        const auto bitset   = bitset_i | bitset_j;
        const auto powerset  = chester::engine::bitset::powerset(bitset);

        CAPTURE(square_i);
        CAPTURE(bitset_i);
        CAPTURE(square_j);
        CAPTURE(bitset_j);

        CAPTURE(bitset);
        CAPTURE(powerset);

        REQUIRE(4 == powerset.size());
        REQUIRE(std::ranges::find_if(powerset, [&](auto entry) -> auto { return entry == bitset; }) != powerset.end());
        REQUIRE(std::ranges::find_if(powerset, [&](auto entry) -> auto { return entry == bitset_i; }) != powerset.end());
        REQUIRE(std::ranges::find_if(powerset, [&](auto entry) -> auto { return entry == bitset_j; }) != powerset.end());
        REQUIRE(std::ranges::find_if(powerset, [&](auto entry) -> auto { return chester::engine::bitset::is_empty(entry); }) != powerset.end());
    }
}
