#pragma once

#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>

#include <ostream>
#include <string>

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

       // clang-format off

namespace chester::engine {

/*
 * Compile-time checks to ensure side and piece values remain
 * consistent with castling logic.
 */
static_assert((int)side::white  == 0);
static_assert((int)side::black  == 1);
static_assert((int)piece::king  == 0);
static_assert((int)piece::queen == 1);

class castling {
  public:
    castling() = default;
    castling(piece piece) {
#ifdef DEBUG
        if (piece.type != piece::king and piece.type != piece::queen) {
            throw std::runtime_error(
                "unable to convert the provided piece to a castling");
        }
#endif // DEBUG
        value = 1UL << (static_cast<unsigned int>(piece.type) +
                       (static_cast<unsigned int>(piece.side) * 2));
    }

    static constexpr auto none() -> castling {
        castling castling;
        castling.value = 0;
        return castling;
    }

    static constexpr auto all() -> castling {
        castling castling;
        castling.value = 0b1111;
        return castling;
    }

    constexpr auto operator==(castling other) const -> bool {
        return value == other.value;
    }

    constexpr auto operator!=(castling other) const -> bool {
        return value != other.value;
    }

    constexpr auto operator~() const -> castling {
        castling castling;
        castling.value = ~this->value;
        return castling;
    }

    constexpr auto operator^=(castling other) { value ^= other.value; }
    constexpr auto operator^(castling other) const -> castling {
        castling castling = *this;
        castling ^= other;
        return castling;
    }

    constexpr auto operator&=(castling other) { value &= other.value; }
    constexpr auto operator&(castling other) const -> castling {
        castling castling = *this;
        castling &= other;
        return castling;
    }

    constexpr auto operator|=(castling other) { value |= other.value; }
    constexpr auto operator|(castling other) const -> castling {
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
    unsigned int value : 4;
};
auto operator<<(std::ostream &os, castling castling) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::castling castling) -> std::string;
}
