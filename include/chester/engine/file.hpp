// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <stdexcept>

namespace chester::engine {

class file {
  public:
    enum value : std::uint8_t {
        a = 0,
        b = 1,
        c = 2,
        d = 3,
        e = 4,
        f = 5,
        g = 6,
        h = 7,
    };

    // cppcheck-suppress noExplicitConstructor
    constexpr file(file::value value) : value(value) {}
    constexpr auto operator==(file other) const { return value == other.value; }
    constexpr auto operator!=(file other) const { return value != other.value; }

    enum file::value value;
};

}

template <>
struct std::formatter<enum chester::engine::file::value> {
    // cppcheck-suppress[unusedFunction,unmatchedSuppression]
    static constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    static auto format(const enum chester::engine::file::value &file, std::format_context &ctx) {
        switch (file) {
            case chester::engine::file::a: return std::format_to(ctx.out(), "a");
            case chester::engine::file::b: return std::format_to(ctx.out(), "b");
            case chester::engine::file::c: return std::format_to(ctx.out(), "c");
            case chester::engine::file::d: return std::format_to(ctx.out(), "d");
            case chester::engine::file::e: return std::format_to(ctx.out(), "e");
            case chester::engine::file::f: return std::format_to(ctx.out(), "f");
            case chester::engine::file::g: return std::format_to(ctx.out(), "g");
            case chester::engine::file::h: return std::format_to(ctx.out(), "h");
        }

        throw std::runtime_error("unknown file");
    }
};


template <>
struct std::formatter<chester::engine::file> : std::formatter<enum chester::engine::file::value> {
    static auto format(const chester::engine::file &file, std::format_context &ctx) {
        return std::format_to(ctx.out(), "{}", file.value);
    }
};

auto operator<<(std::ostream &os, enum chester::engine::file::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::file        const &value) -> std::ostream &;

// NOLINTEND
