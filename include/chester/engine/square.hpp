// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <format>
#include <ostream>

#include <chester/engine/file.hpp>
#include <chester/engine/rank.hpp>

namespace chester::engine {

class square {
  public:
    enum value : std::uint8_t {
        a1 = 0, a2 =  8, a3 = 16, a4 = 24, a5 = 32, a6 = 40, a7 = 48, a8 = 56,
        b1 = 1, b2 =  9, b3 = 17, b4 = 25, b5 = 33, b6 = 41, b7 = 49, b8 = 57,
        c1 = 2, c2 = 10, c3 = 18, c4 = 26, c5 = 34, c6 = 42, c7 = 50, c8 = 58,
        d1 = 3, d2 = 11, d3 = 19, d4 = 27, d5 = 35, d6 = 43, d7 = 51, d8 = 59,
        e1 = 4, e2 = 12, e3 = 20, e4 = 28, e5 = 36, e6 = 44, e7 = 52, e8 = 60,
        f1 = 5, f2 = 13, f3 = 21, f4 = 29, f5 = 37, f6 = 45, f7 = 53, f8 = 61,
        g1 = 6, g2 = 14, g3 = 22, g4 = 30, g5 = 38, g6 = 46, g7 = 54, g8 = 62,
        h1 = 7, h2 = 15, h3 = 23, h4 = 31, h5 = 39, h6 = 47, h7 = 55, h8 = 63,
    };

    // cppcheck-suppress noExplicitConstructor
    constexpr square(square::value value) : value(value) {}
    constexpr square(chester::engine::file file, chester::engine::rank rank)
        : value((enum square::value)((rank.value * 8) + file.value)) {}

    constexpr auto operator==(square other) const { return value == other.value; }
    constexpr auto operator!=(square other) const { return value != other.value; }

    [[nodiscard]]
    constexpr auto file() const -> chester::engine::file {
        return (enum chester::engine::file::value)(value % 8);
    }

    [[nodiscard]]
    constexpr auto rank() const -> chester::engine::rank {
        return (enum chester::engine::rank::value)(value / 8);
    }

    enum square::value value;
};

} // namespace chester::engine


constexpr auto operator==(chester::engine::square lhs, enum chester::engine::square::value rhs) {
    return lhs.value == rhs;
}

constexpr auto operator==(enum chester::engine::square::value lhs, chester::engine::square rhs) {
    return lhs == rhs.value;
}

constexpr auto operator!=(chester::engine::square lhs, enum chester::engine::square::value rhs) {
    return lhs.value != rhs;
}

constexpr auto operator!=(enum chester::engine::square::value lhs, chester::engine::square rhs) {
    return lhs != rhs.value;
}

template<>
struct std::formatter<chester::engine::square> {
    // cppcheck-suppress[unusedFunction,unmatchedSuppression]
    static constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    static auto format(const chester::engine::square &square, std::format_context &ctx) {
        return std::format_to(ctx.out(), "{}{}", square.file(), square.rank());
    }
};

template<>
struct std::formatter<enum chester::engine::square::value> : std::formatter<chester::engine::square> {
    static auto format(const enum chester::engine::square::value &square, std::format_context &ctx) {
        return std::format_to(ctx.out(), "{}", chester::engine::square(square));
    }
};

auto operator<<(std::ostream &os, enum chester::engine::square::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::square        const &value) -> std::ostream &;

// NOLINTEND
