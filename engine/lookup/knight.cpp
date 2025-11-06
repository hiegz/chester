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

/** lookup table for pseudo-legal moves of a knight */
class table {
  public:
    std::array<chester::engine::bitboard, SQUARES> cells;

    table() : cells() {
        for (std::uint8_t i = 0; i < SQUARES; ++i) {
            const auto square = (class square)(enum square::value)i;
            const auto file   = square.file();
            const auto rank   = square.rank();

            auto moves = bitboard::empty();

            // . . . x .
            // . . . . .
            // . . N . .
            // . . . . .
            // . . . . .
            if (file < file::h and rank <= rank::six) {
                moves |= square >> 17;
            }

            // . . . . .
            // . . . . x
            // . . N . .
            // . . . . .
            // . . . . .
            if (file < file::g and rank <= rank::seven) {
                moves |= square >> 10;
            }

            // . . . . .
            // . . . . .
            // . . N . .
            // . . . . x
            // . . . . .
            if (file < file::g and rank >= rank::two) {
                moves |= square << 6;
            }

            // . . . . .
            // . . . . .
            // . . N . .
            // . . . . .
            // . . . x .
            if (file < file::h and rank >= rank::three) {
                moves |= square << 15;
            }

            // . . . . .
            // . . . . .
            // . . N . .
            // . . . . .
            // . x . . .
            if (file > file::a and rank >= rank::three) {
                moves |= square << 17;
            }

            // . . . . .
            // . . . . .
            // . . N . .
            // x . . . .
            // . . . . .
            if (file > file::b and rank >= rank::two) {
                moves |= square << 10;
            }

            // . . . . .
            // x . . . .
            // . . N . .
            // . . . . .
            // . . . . .
            if (file > file::b and rank <= rank::seven) {
                moves |= square >> 6;
            }

            // . x . . .
            // . . . . .
            // . . N . .
            // . . . . .
            // . . . . .
            if (file > file::a and rank <= rank::six) {
                moves |= square >> 15;
            }

            this->cells[i] = moves;
        }
    }
};

} // namespace

template <>
auto chester::engine::lookup<piece::knight>(square square)
    -> chester::engine::bitboard {
    static ::table table;
    return table.cells[square.value];
}

// NOLINTEND
