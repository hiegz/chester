#pragma once

#include <array>
#include <ostream>
#include <string>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>

namespace chester::engine {

// clang-format off

class board {
  public:
    constexpr static auto empty() -> board {
        board b;
        for (auto &piece : b.pieces) {
            piece = bitboard::empty();
        }
        return b;
    }

    constexpr auto operator[](chester::engine::piece const &piece) const -> bitboard const & {
        return pieces[(6 * static_cast<unsigned int>(piece.side)) + static_cast<unsigned int>(piece.type)];
    }

    constexpr auto operator[](chester::engine::piece const &piece) -> bitboard & {
        return pieces[(6 * static_cast<unsigned int>(piece.side)) + static_cast<unsigned int>(piece.type)];
    }

    // auto operator==(board const &other) const {
    //     // NOLINTNEXTLINE
    //     for (int i = 0; i < 12; ++i) {
    //         if (this->pieces[i] != other.pieces[i]) {
    //             return false;
    //         }
    //     }

    //     return true;
    // }

    // auto operator!=(board const &other) const {
    //     return not (*this == other);
    // }

  private:
    std::array<bitboard, 12> pieces; // NOLINT
};

auto operator<<(std::ostream &os, chester::engine::board const &board)
    -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::board const &board) -> std::string;
}
