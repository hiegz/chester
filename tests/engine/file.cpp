#include <catch2/catch_test_macros.hpp>
#include <chester/engine/file.hpp>
#include <string>

using chester::engine::file;

// clang-format off

static_assert(file::a      > file::low);
static_assert(file::a - 1  == file::low);
static_assert(file::a - 2  <  file::low);
static_assert(file::a - 10 <  file::low);
static_assert(file::h      <  file::high);
static_assert(file::h + 1  == file::high);
static_assert(file::h + 2  > file::high);
static_assert(file::h + 10 > file::high);

TEST_CASE("chester::engine::files validity", "[engine][file]") {
    for (const auto file : chester::engine::files) {
        REQUIRE(file.valid());
    }
}

TEST_CASE("std::to_string(chester::engine::file)", "[engine][file][fmt]") {
    REQUIRE("a" == std::to_string(file::a));
    REQUIRE("b" == std::to_string(file::b));
    REQUIRE("c" == std::to_string(file::c));
    REQUIRE("d" == std::to_string(file::d));
    REQUIRE("e" == std::to_string(file::e));
    REQUIRE("f" == std::to_string(file::f));
    REQUIRE("g" == std::to_string(file::g));
    REQUIRE("h" == std::to_string(file::h));
    REQUIRE("?" == std::to_string(file::low));
    REQUIRE("?" == std::to_string(file::low - 1));
    REQUIRE("?" == std::to_string(file::high));
    REQUIRE("?" == std::to_string(file::high + 1));
}
