#pragma once

#include <algorithm>
#include <array>
#include <ostream>
#include <string>

#include <chester/engine/bitset.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>

namespace chester::engine {

// clang-format off

class bitboard {
  public:
    constexpr static auto empty() -> bitboard {
        bitboard b;
        std::ranges::fill(b.pieces, bitset::empty());
        return b;
    }

    static auto traditional() -> bitboard;

    constexpr auto operator==(bitboard const &) const -> bool = default;
    constexpr auto operator!=(bitboard const &) const -> bool = default;

    constexpr auto operator[](chester::engine::piece const &piece) const -> bitset const & {
        return pieces[(6 * static_cast<unsigned int>(piece.side)) + static_cast<unsigned int>(piece.type)];
    }

    constexpr auto operator[](chester::engine::piece const &piece) -> bitset & {
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
    std::array<bitset, 12> pieces; // NOLINT
};

auto operator<<(std::ostream &os, chester::engine::bitboard const &board)
    -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::bitboard const &board) -> std::string;
}
