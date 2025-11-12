// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

#include <chester/engine/square.hpp>
#include <chester/engine/bitset.hpp>

namespace chester::engine {

/**
 * 64-bit word used to represent a chessboard.
 *
 * This class extends the 64-bit unsigned integer to implement general setwise
 * operations, population count, bitscan, mirroring, and formatting.
 */
class bitboard {
  public:
    uint64_t value;

    constexpr bitboard() {};
    // cppcheck-suppress noExplicitConstructor
    constexpr bitboard(chester::engine::square square)
        : value(1UL << square.value) {}
    // cppcheck-suppress noExplicitConstructor
    constexpr bitboard(enum chester::engine::square::value square)
        : value(1UL << square) {}

    constexpr auto operator==(bitboard other) const -> bool     { return  value == other.value; }
    constexpr auto operator!=(bitboard other) const -> bool     { return  value != other.value; }
    constexpr auto operator& (bitboard other) const -> bitboard { return  value &  other.value; }
    constexpr auto operator| (bitboard other) const -> bitboard { return  value |  other.value; }
    constexpr auto operator^ (bitboard other) const -> bitboard { return  value ^  other.value; }
    constexpr auto operator~()                const -> bitboard { return ~value;                }
    constexpr auto operator&=(bitboard other)                   {         value &= other.value; }
    constexpr auto operator|=(bitboard other)                   {         value |= other.value; }
    constexpr auto operator^=(bitboard other)                   {         value ^= other.value; }

    // Bitset operations

    constexpr static auto empty() -> bitboard { return bitboard(bitset::empty<std::uint64_t>()); }
    constexpr static auto universal() -> bitboard { return bitboard(bitset::universal<std::uint64_t>()); }
    constexpr auto is_empty() const { return bitset::is_empty(value); }
    constexpr auto is_universal() const { return bitset::is_universal(value); }
    constexpr auto is_single() const { return bitset::is_single(value); }
    constexpr auto cardinality() const { return bitset::cardinality(value); }
    constexpr auto scan_forward() const -> square { return (enum square::value)bitset::scan_forward(value); }
    constexpr auto scan_backward() const -> square { return (enum square::value)bitset::scan_backward(value); }
    constexpr auto pop_front() -> square { return (enum square::value)bitset::pop_front(&value); }
    constexpr auto pop_back() -> square { return (enum square::value)bitset::pop_back(&value); }

    /**
     * Returns the n-th subset of the given bitboard.
     *
     * For performance, the bitboard's cardinality is provided by the caller so
     * it is not recomputed for every subset. It goes without saying that providing
     * an incorrect cardinality results in undefined behavior.
     *
     * The `index` specifies which subset to return and must be within the range [0, 1 << cardinality).
     */
    constexpr static auto subset(class bitboard bitboard, std::size_t cardinality, std::size_t index) -> class bitboard {
        return bitset::subset(bitboard.value, cardinality, index);
    }

    /**
     * Mirror a bitboard horizontally about the center files.
     *
     * File a is mapped to file h and vice versa.
     */
    constexpr auto mirror() {
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        // . 1 . 1 . 1 . 1
        constexpr std::uint64_t K1 = 0x5555555555555555UL;

        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        // . . 1 1 . . 1 1
        constexpr std::uint64_t K2 = 0x3333333333333333UL;

        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        // . . . . 1 1 1 1
        constexpr std::uint64_t K4 = 0x0f0f0f0f0f0f0f0fUL;

        //

        value = ((value >> 1) & K1) | ((value & K1) << 1);
        value = ((value >> 2) & K2) | ((value & K2) << 2);
        value = ((value >> 4) & K4) | ((value & K4) << 4);
    }

    constexpr static auto mirror(bitboard other) -> bitboard {
        bitboard copy = other;
        copy.mirror();
        return copy;
    }

  private:
    // cppcheck-suppress noExplicitConstructor
    constexpr bitboard(std::uint64_t value) : value(value) {}
};

auto operator<<(std::ostream &os, chester::engine::bitboard const &bitboard) -> std::ostream &;

}

namespace std {

auto to_string(chester::engine::bitboard) -> std::string;

}


constexpr auto chester::engine::operator&(square lhs, square rhs) -> bitboard {
    return bitboard(lhs) & bitboard(rhs);
}

constexpr auto chester::engine::operator|(square lhs, square rhs) -> bitboard {
    return bitboard(lhs) | bitboard(rhs);
}

constexpr auto chester::engine::operator^(square lhs, square rhs) -> bitboard {
    return bitboard(lhs) ^ bitboard(rhs);
}

constexpr auto chester::engine::operator~(square lhs) -> bitboard {
    return ~bitboard(lhs);
}

constexpr auto chester::engine::operator&(enum square::value lhs, enum square::value rhs) -> bitboard {
    return square(lhs) & square(rhs);
};

constexpr auto chester::engine::operator|(enum square::value lhs, enum square::value rhs) -> bitboard {
    return square(lhs) | square(rhs);
}

constexpr auto chester::engine::operator^(enum square::value lhs, enum square::value rhs) -> bitboard {
    return square(lhs) ^ square(rhs);
}

constexpr auto chester::engine::operator~(enum square::value lhs) -> bitboard {
    return ~square(lhs);
}

// NOLINTEND
