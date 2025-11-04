// clang-format off

#include <format>
#include <sstream>

#include <chester/engine/rank.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

using chester::engine::rank;

TEST_CASE("chester::engine::rank::value operator << overload for std::ostream", "[engine][rank::value][fmt]") {
    std::ostringstream ostr;

    SECTION("one") {
        const enum rank::value rank = rank::one;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("1" == ostr.str());
    }

    SECTION("two") {
        const enum rank::value rank = rank::two;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("2" == ostr.str());
    }

    SECTION("three") {
        const enum rank::value rank = rank::three;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("3" == ostr.str());
    }

    SECTION("four") {
        const enum rank::value rank = rank::four;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("4" == ostr.str());
    }

    SECTION("five") {
        const enum rank::value rank = rank::five;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("5" == ostr.str());
    }

    SECTION("six") {
        const enum rank::value rank = rank::six;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("6" == ostr.str());
    }

    SECTION("seven") {
        const enum rank::value rank = rank::seven;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("7" == ostr.str());
    }

    SECTION("eight") {
        const enum rank::value rank = rank::eight;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("8" == ostr.str());
    }
}

TEST_CASE("chester::engine::rank operator << overload for std::ostream", "[engine][rank][fmt]") {
    std::ostringstream ostr;

    SECTION("one") {
        const rank rank = rank::one;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("1" == ostr.str());
    }

    SECTION("two") {
        const rank rank = rank::two;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("2" == ostr.str());
    }

    SECTION("three") {
        const rank rank = rank::three;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("3" == ostr.str());
    }

    SECTION("four") {
        const rank rank = rank::four;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("4" == ostr.str());
    }

    SECTION("five") {
        const rank rank = rank::five;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("5" == ostr.str());
    }

    SECTION("six") {
        const rank rank = rank::six;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("6" == ostr.str());
    }

    SECTION("seven") {
        const rank rank = rank::seven;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("7" == ostr.str());
    }

    SECTION("eight") {
        const rank rank = rank::eight;
        CAPTURE(rank);
        ostr << rank;
        REQUIRE("8" == ostr.str());
    }
}
