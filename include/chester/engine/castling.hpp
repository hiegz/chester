#pragma once

#include <chester/engine/castling_type.hpp>
#include <chester/engine/side.hpp>

#include <ostream>
#include <string>

namespace chester::engine {

// clang-format off

/*
 * Compile-time checks to ensure side and castling type values remain
 * consistent with the castling logic.
 */
static_assert((int)side::white  == 0);
static_assert((int)side::black  == 1);
static_assert((int)castling_type::kingside == 0);
static_assert((int)castling_type::queenside == 1);

class castling {
  public:
    static const castling none;
    static const castling all;
    static const castling white_kingside;
    static const castling white_queenside;
    static const castling black_kingside;
    static const castling black_queenside;

    constexpr castling() = default;
    template <typename T>
    constexpr explicit castling(T raw) : raw(static_cast<unsigned int>(raw)) {}
    constexpr operator unsigned int() const { return raw; }
    constexpr castling(side side, castling_type type)
        : raw(1UL << static_cast<unsigned int>((2 * side) + type))
    {}

    constexpr auto operator==(castling other) const -> bool {
        return raw == other.raw;
    }

    constexpr auto operator!=(castling other) const -> bool {
        return raw != other.raw;
    }

    constexpr auto operator~() const -> castling {
        castling castling;
        castling.raw = ~this->raw;
        return castling;
    }

    constexpr auto operator^=(castling other) { raw ^= other.raw; }
    constexpr auto operator^ (castling other) const -> castling {
        castling castling = *this;
        castling ^= other;
        return castling;
    }

    constexpr auto operator&=(castling other) { raw &= other.raw; }
    constexpr auto operator& (castling other) const -> castling {
        castling castling = *this;
        castling &= other;
        return castling;
    }

    constexpr auto operator|=(castling other) { raw |= other.raw; }
    constexpr auto operator| (castling other) const -> castling {
        castling castling = *this;
        castling |= other;
        return castling;
    }

    friend auto operator<<(std::ostream &os, castling castling)
        -> std::ostream &;

  private:
    /**
     * (right-to-left numbering)
     *
     * 1st bit represents white kingside castling
     * 2nd bit represents white queenside castling
     * 3rd bit represents black kingside castling
     * 4th bit represents black queenside
     */
    unsigned int raw : 4;
};

constexpr castling castling::none            = castling(0);
constexpr castling castling::all             = castling(0b1111);
constexpr castling castling::white_kingside  = castling(side::white, castling_type::kingside);
constexpr castling castling::white_queenside = castling(side::white, castling_type::queenside);
constexpr castling castling::black_kingside  = castling(side::black, castling_type::kingside);
constexpr castling castling::black_queenside = castling(side::black, castling_type::queenside);

auto operator<<(std::ostream &os, castling castling) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::castling castling) -> std::string;
}
