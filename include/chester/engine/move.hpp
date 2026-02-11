#pragma once

#include <chester/engine/move_type.hpp>
#include <chester/engine/piece_type.hpp>
#include <chester/engine/square.hpp>

#include <cstdint>
#include <ostream>
#include <string>
#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

// clang-format off

namespace chester::engine {

class move {
  public:
    std::uint16_t raw;

    constexpr move() = default;
    template <typename T>
    constexpr explicit move(T raw) : raw(static_cast<std::uint16_t>(raw)) {}
    constexpr operator std::uint16_t() const { return raw; }

    constexpr move(square     origin,
                   square     destination,
                   move_type  type,
                   piece_type promotion_piece = piece_type::queen)
        : raw(0)
    {
#ifdef DEBUG
        if (origin.invalid()) {
            throw std::runtime_error("invalid origin");
        }

        if (destination.invalid()) {
            throw std::runtime_error("invalid destination");
        }

        if (type.invalid()) {
            throw std::runtime_error("invalid move type");
        }

        if (promotion_piece.invalid()
              || promotion_piece == piece_type::pawn
              || promotion_piece == piece_type::king) {
            throw std::runtime_error("invalid promotion piece");
        }
#endif // DEBUG

        raw |= (static_cast<unsigned int>(origin.raw)          << 0U);
        raw |= (static_cast<unsigned int>(destination.raw)     << 6U);
        raw |= (static_cast<unsigned int>(promotion_piece.raw) << 12U);
        raw |= (static_cast<unsigned int>(type.raw));
    }

    [[nodiscard]] constexpr auto origin()          const -> square;
    [[nodiscard]] constexpr auto destination()     const -> square;
    [[nodiscard]] constexpr auto type()            const -> move_type;
    [[nodiscard]] constexpr auto promotion_piece() const -> piece_type;
};

[[nodiscard]]
constexpr auto move::origin() const -> square {
    return square(static_cast<unsigned int>(raw >> 0U) & 0b111111U);
}

[[nodiscard]]
constexpr auto move::destination() const -> square {
    return square(static_cast<unsigned int>(raw >> 6U) & 0b111111U);
}

[[nodiscard]]
constexpr auto move::type() const -> move_type {
    return move_type(raw & (0b11U << 14U));
}

[[nodiscard]]
constexpr auto move::promotion_piece() const -> piece_type {
#ifdef DEBUG
    if (type() != move_type::promotion) {
        throw std::runtime_error("promotion piece is not defined for non-promotion moves");
    }
#endif // DEBUG

    return piece_type(static_cast<unsigned int>(raw >> 12U) & 0b11U);
}


auto operator<<(std::ostream &os, move move) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::move move) -> std::string;
}
