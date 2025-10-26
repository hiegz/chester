// clang-format off

#include <format>
#include <sstream>

#include <chester/engine/file.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

using chester::engine::file;

TEST_CASE("chester::engine::file::value formatter", "[engine][file::value][fmt]") {
    REQUIRE("a" == std::format("{}", file::a));
    REQUIRE("b" == std::format("{}", file::b));
    REQUIRE("c" == std::format("{}", file::c));
    REQUIRE("d" == std::format("{}", file::d));
    REQUIRE("e" == std::format("{}", file::e));
    REQUIRE("f" == std::format("{}", file::f));
    REQUIRE("g" == std::format("{}", file::g));
    REQUIRE("h" == std::format("{}", file::h));
}

TEST_CASE("chester::engine::file::value operator << overload for std::ostream", "[engine][file::value][fmt]") {
    std::ostringstream ostr;

    SECTION("file a") {
        const enum file::value file = file::a;
        CAPTURE(file);
        ostr << file;
        REQUIRE("a" == ostr.str());
    }

    SECTION("file b") {
        const enum file::value file = file::b;
        CAPTURE(file);
        ostr << file;
        REQUIRE("b" == ostr.str());
    }

    SECTION("file c") {
        const enum file::value file = file::c;
        CAPTURE(file);
        ostr << file;
        REQUIRE("c" == ostr.str());
    }

    SECTION("file d") {
        const enum file::value file = file::d;
        CAPTURE(file);
        ostr << file;
        REQUIRE("d" == ostr.str());
    }

    SECTION("file e") {
        const enum file::value file = file::e;
        CAPTURE(file);
        ostr << file;
        REQUIRE("e" == ostr.str());
    }

    SECTION("file f") {
        const enum file::value file = file::f;
        CAPTURE(file);
        ostr << file;
        REQUIRE("f" == ostr.str());
    }

    SECTION("file g") {
        const enum file::value file = file::g;
        CAPTURE(file);
        ostr << file;
        REQUIRE("g" == ostr.str());
    }

    SECTION("file h") {
        const enum file::value file = file::h;
        CAPTURE(file);
        ostr << file;
        REQUIRE("h" == ostr.str());
    }
}

TEST_CASE("chester::engine::file formatter", "[engine][file][fmt]") {
    REQUIRE("a" == std::format("{}", (file)file::a));
    REQUIRE("b" == std::format("{}", (file)file::b));
    REQUIRE("c" == std::format("{}", (file)file::c));
    REQUIRE("d" == std::format("{}", (file)file::d));
    REQUIRE("e" == std::format("{}", (file)file::e));
    REQUIRE("f" == std::format("{}", (file)file::f));
    REQUIRE("g" == std::format("{}", (file)file::g));
    REQUIRE("h" == std::format("{}", (file)file::h));
}

TEST_CASE("chester::engine::file operator << overload for std::ostream", "[engine][file][fmt]") {
    std::ostringstream ostr;

    SECTION("file a") {
        const file file = file::a;
        CAPTURE(file);
        ostr << file;
        REQUIRE("a" == ostr.str());
    }

    SECTION("file b") {
        const file file = file::b;
        CAPTURE(file);
        ostr << file;
        REQUIRE("b" == ostr.str());
    }

    SECTION("file c") {
        const file file = file::c;
        CAPTURE(file);
        ostr << file;
        REQUIRE("c" == ostr.str());
    }

    SECTION("file d") {
        const file file = file::d;
        CAPTURE(file);
        ostr << file;
        REQUIRE("d" == ostr.str());
    }

    SECTION("file e") {
        const file file = file::e;
        CAPTURE(file);
        ostr << file;
        REQUIRE("e" == ostr.str());
    }

    SECTION("file f") {
        const file file = file::f;
        CAPTURE(file);
        ostr << file;
        REQUIRE("f" == ostr.str());
    }

    SECTION("file g") {
        const file file = file::g;
        CAPTURE(file);
        ostr << file;
        REQUIRE("g" == ostr.str());
    }

    SECTION("file h") {
        const file file = file::h;
        CAPTURE(file);
        ostr << file;
        REQUIRE("h" == ostr.str());
    }
}
