#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

#ifdef DEBUG
#include <stdexcept>
#endif

#include <chester/engine/square.hpp>

// clang-format off

namespace chester::engine {

/**
 * This class extends the 64-bit unsigned integer to implement general setwise
 * operations, population count, bitscan, mirroring, and formatting.
 */
class bitset {
  public:
    uint64_t raw;

    constexpr bitset() = default;
    constexpr bitset(chester::engine::square sq) {
        if (sq == square::none) {
            raw = 0;
            return;
        }

#ifdef DEBUG
        if (sq.invalid()) {
            throw std::runtime_error("unable to construct a bitboard from invalid square");
        }
#endif // DEBUG

        // clang-analyzer incorrectly reports the following shift as a
        // potential integer overflow even though the prior validation
        // ensures the square index is always within [0, 63].

        // NOLINTNEXTLINE
        raw = (1UL << static_cast<unsigned char>(sq.raw));
    }

    constexpr auto operator==(bitset other) const -> bool   { return  raw == other.raw; }
    constexpr auto operator!=(bitset other) const -> bool   { return  raw != other.raw; }
    constexpr auto operator& (bitset other) const -> bitset { return  raw &  other.raw; }
    constexpr auto operator| (bitset other) const -> bitset { return  raw |  other.raw; }
    constexpr auto operator^ (bitset other) const -> bitset { return  raw ^  other.raw; }
    constexpr auto operator~()              const -> bitset { return ~raw;                }
    constexpr auto operator&=(bitset other)                 {         raw &= other.raw; }
    constexpr auto operator|=(bitset other)                 {         raw |= other.raw; }
    constexpr auto operator^=(bitset other)                 {         raw ^= other.raw; }

    // Bitwise operations

    /** Returns an empty bitset */
    constexpr static auto empty() -> bitset {
        return {0};
    }

    /** Returns a universal bitset */
    constexpr static auto universal() -> bitset {
        return {0xFFFFFFFFFFFFFFFF};
    }

    /** Checks if a bitset is single populated */
    [[nodiscard]]
    constexpr auto single() const -> bool {
        return raw != 0 and (raw & (raw - 1)) == 0;
    }

    /** Returns the cardinality of a bitset */
    [[nodiscard]]
    constexpr auto cardinality() const -> std::size_t {
        std::size_t count = 0;
        std::uint64_t value = this->raw;
        while (value != 0) {
            count += 1;
            value &= value - 1;
        }
        return count;
    }

    /**
     * Returns the position of the first least significant set bit.
     *
     * This function assumes the bitset is not empty.
     */
    [[nodiscard]]
    constexpr auto scan_forward() const -> square {
#ifdef DEBUG
        if (*this == bitset::empty()) {
            throw std::runtime_error("bitset is empty");
        }
#endif
        return square(std::countr_zero(raw));
    }

    /**
     * Return the position of the first most significant set bit.
     *
     * This function assumes the bitset is not empty.
     */
    [[nodiscard]]
    constexpr auto scan_backward() const -> square {
#ifdef DEBUG
        if (*this == bitset::empty()) {
            throw std::runtime_error("bitset is empty");
        }
#endif
        return square(63 - std::countl_zero(raw));
    }

    /**
     * Removes the first least significant bit and returns its position.
     *
     * This function assumes the bitset is not empty.
     */
    constexpr auto pop_front() -> square {
        const square sq = scan_forward();
        *this ^= sq;
        return sq;
    }

    /**
     * Removes the first most significant bit and returns its position.
     *
     * This function assumes the bitset is not empty.
     */
    constexpr auto pop_back() -> square {
        const square sq = scan_backward();
        *this ^= sq;
        return sq;
    }

    /**
     * Returns the n-th subset of the given bitset.
     *
     * For performance, the bitset's cardinality is provided by the caller so
     * it is not recomputed for every subset. It goes without saying that providing
     * an incorrect cardinality results in undefined behavior.
     *
     * The `index` specifies which subset to return and must be within the range [0, 1 << cardinality).
     */
    [[nodiscard]]
    constexpr auto subset(std::size_t cardinality, std::size_t index) const -> bitset {
#ifdef DEBUG
        if (cardinality != this->cardinality()) {
            throw std::runtime_error("provided bitset cardinality does not match its real cardinality");
        }

        if (index >= (1UL << cardinality)) {
            throw std::runtime_error("index is out of bounds");
        }
#endif

        bitset mask = raw;
        bitset result = 0;

        for (std::size_t i = 0; i < cardinality; ++i) {
            const square j = mask.pop_front();
            if ((index & (1UL << i)) != 0) {
                result |= j;
            }
        }

        return result;
    }

    /**
     * Mirror a bitset horizontally about the center files.
     *
     * File a is mapped to file h and vice versa.
     */
    [[nodiscard]]
    constexpr auto mirror() const -> bitset {
        std::uint64_t ret = this->raw;

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

        ret = ((ret >> 1U) & K1) | ((ret & K1) << 1U);
        ret = ((ret >> 2U) & K2) | ((ret & K2) << 2U);
        ret = ((ret >> 4U) & K4) | ((ret & K4) << 4U);

        return {ret};
    }

  private:
    // cppcheck-suppress noExplicitConstructor
    constexpr bitset(std::uint64_t value) : raw(value) {}
};

constexpr auto operator&(square a, square b) -> bitset {
    return bitset(a) & bitset(b);
}

constexpr auto operator|(square a, square b) -> bitset {
    return bitset(a) | bitset(b);
}

constexpr auto operator^(square a, square b) -> bitset {
    return bitset(a) ^ bitset(b);
}

constexpr auto operator~(square sq) -> bitset {
    return ~bitset(sq);
}

auto operator<<(std::ostream &os, bitset bitset) -> std::ostream &;

}

namespace std {
auto to_string(chester::engine::bitset bitset) -> std::string;
}
