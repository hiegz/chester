// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

#include <chester/engine/file.hpp>
#include <chester/engine/rank.hpp>

namespace chester::engine {

class bitboard;

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

    constexpr square() : value(square::a1) {}

    // cppcheck-suppress noExplicitConstructor
    constexpr square(square::value value) : value(value) {}
    constexpr square(chester::engine::file file, chester::engine::rank rank)
        : value((enum square::value)((rank.value * 8) + file.value)) {}

    [[nodiscard]]
    constexpr auto file() const -> chester::engine::file {
        return square::file(value);
    }

    [[nodiscard]]
    constexpr static auto file(square::value value) -> chester::engine::file {
        return (enum chester::engine::file::value)(value % 8);
    }

    [[nodiscard]]
    constexpr static auto file(square square) -> chester::engine::file {
        return file(square.value);
    }

    [[nodiscard]]
    constexpr auto rank() const -> chester::engine::rank {
        return square::rank(value);
    }

    [[nodiscard]]
    constexpr static auto rank(square::value value) -> chester::engine::rank {
        return (enum chester::engine::rank::value)(value / 8);
    }

    [[nodiscard]]
    constexpr static auto rank(square square) -> chester::engine::rank {
        return rank(square.value);
    }

    enum square::value value;
};

constexpr auto operator==(square lhs, square rhs) {
    return lhs.value == rhs.value;
}

constexpr auto operator!=(square lhs, square rhs) {
    return lhs.value != rhs.value;
}

constexpr auto operator<<(enum square::value lhs, int rhs) -> enum square::value {
#ifdef DEBUG
    if (lhs - rhs < 0)
        throw std::runtime_error("left shift resulted in an invalid square");
#endif
    return (enum square::value)(lhs - rhs);
}

constexpr auto operator<<=(enum square::value &lhs, int rhs) {
    lhs = lhs << rhs;
}

constexpr auto operator>>(enum square::value lhs, int rhs) -> enum square::value {
#ifdef DEBUG
    if (lhs + rhs > 63)
        throw std::runtime_error("left shift resulted in an invalid square");
#endif
    return (enum square::value)(lhs + rhs);
}

constexpr auto operator>>=(enum square::value &lhs, int rhs) {
    lhs = lhs >> rhs;
}

constexpr auto operator<<(square lhs, int rhs) -> square {
    return square(lhs.value << rhs);
}

constexpr auto operator<<=(square &lhs, int rhs) {
    lhs = lhs << rhs;
}

constexpr auto operator>>(square lhs, int rhs) -> square {
    return square(lhs.value >> rhs);
}

constexpr auto operator>>=(square &lhs, int rhs) {
    lhs = lhs >> rhs;
}

constexpr auto operator&(     square        lhs,      square        rhs) -> bitboard;
constexpr auto operator|(     square        lhs,      square        rhs) -> bitboard;
constexpr auto operator^(     square        lhs,      square        rhs) -> bitboard;
constexpr auto operator~(     square        lhs)                         -> bitboard;
constexpr auto operator&(enum square::value lhs, enum square::value rhs) -> bitboard;
constexpr auto operator|(enum square::value lhs, enum square::value rhs) -> bitboard;
constexpr auto operator^(enum square::value lhs, enum square::value rhs) -> bitboard;
constexpr auto operator~(enum square::value lhs)                         -> bitboard;

auto operator<<(std::ostream &os, enum chester::engine::square::value const &value)  -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::square        const &square) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(     chester::engine::square        square) -> std::string;
auto to_string(enum chester::engine::square::value value)  -> std::string;
}

// NOLINTEND
