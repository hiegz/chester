// NOLINTBEGIN

#include <array>
#include <cstddef>
#include <cstdint>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/square.hpp>

using chester::engine::bitboard;
using chester::engine::file;
using chester::engine::piece;
using chester::engine::rank;
using chester::engine::square;

namespace {

const std::size_t SQUARES = 64;

/** lookup table for pseudo-legal moves of a kin*/
class table {
  public:
    std::array<chester::engine::bitboard, SQUARES> cells;

    table() : cells() {
        for (std::uint8_t i = 0; i < SQUARES; ++i) {
            const auto square = (class square)(enum square::value)i;
            const auto file   = square.file();
            const auto rank   = square.rank();

            auto moves = bitboard::empty();

            // . x .
            // . K .
            // . . .
            if (rank < rank::eight) {
                moves |= square >> 8;
            }

            // . . x
            // . K .
            // . . .
            if (file < file::h and rank < rank::eight) {
                moves |= square >> 9;
            }

            // . . .
            // . K x
            // . . .
            if (file < file::h) {
                moves |= square >> 1;
            }

            // . . .
            // . K .
            // . . x
            if (file < file::h and rank > rank::one) {
                moves |= square << 7;
            }

            // . . .
            // . K .
            // . x .
            if (rank > rank::one) {
                moves |= square << 8;
            }

            // . . .
            // . K .
            // x . .
            if (file > file::a and rank > rank::one) {
                moves |= square << 9;
            }

            // . . .
            // x K .
            // . . .
            if (file > file::a) {
                moves |= square << 1;
            }

            // x . .
            // . K .
            // . . .
            if (file > file::a and rank < rank::eight) {
                moves |= square >> 7;
            }

            this->cells[i] = moves;
        }
    }
};

} // namespace

template <>
auto chester::engine::lookup<piece::king>(square square)
    -> chester::engine::bitboard {
    static ::table table;
    return table.cells[square.value];
}

// NOLINTEND
