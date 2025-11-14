#include <catch2/catch_test_macros.hpp>
#include <chester/engine/rank.hpp>
#include <string>

using chester::engine::rank;

// clang-format off

static_assert(rank::one        >  rank::low);
static_assert(rank::one   - 1  == rank::low);
static_assert(rank::one   - 2  <  rank::low);
static_assert(rank::one   - 10 <  rank::low);
static_assert(rank::eight      <  rank::high);
static_assert(rank::eight + 1  == rank::high);
static_assert(rank::eight + 2  >  rank::high);
static_assert(rank::eight + 10 >  rank::high);

TEST_CASE("chester::engine::ranks validity", "[engine][rank]") {
    for (const auto rank : chester::engine::ranks) {
        REQUIRE(rank.valid());
    }
}

TEST_CASE("std::to_string(chester::engine::rank)", "[engine][rank][fmt]") {
    REQUIRE("1" == std::to_string(rank::one));
    REQUIRE("2" == std::to_string(rank::two));
    REQUIRE("3" == std::to_string(rank::three));
    REQUIRE("4" == std::to_string(rank::four));
    REQUIRE("5" == std::to_string(rank::five));
    REQUIRE("6" == std::to_string(rank::six));
    REQUIRE("7" == std::to_string(rank::seven));
    REQUIRE("8" == std::to_string(rank::eight));
    REQUIRE("?" == std::to_string(rank::low));
    REQUIRE("?" == std::to_string(rank::low - 1));
    REQUIRE("?" == std::to_string(rank::high));
    REQUIRE("?" == std::to_string(rank::high + 1));
}
