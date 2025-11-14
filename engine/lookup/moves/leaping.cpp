#include <array>
#include <cstddef>
#include <cstdint>

#include <chester/engine/bitset.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/square.hpp>

using chester::engine::bitset;
using chester::engine::file;
using chester::engine::piece;
using chester::engine::rank;
using chester::engine::square;

namespace {

constexpr std::size_t SQUARES = 64;

namespace king {

/** lookup table for pseudo-legal moves of a kin*/
class table {
  public:
    std::array<chester::engine::bitset, SQUARES> cells;

    table() : cells() {
        for (std::uint8_t i = 0; i < SQUARES; ++i) {
            const auto square = (class square)i;
            const auto file   = square.file();
            const auto rank   = square.rank();

            auto moves = bitset::empty();

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

} // namespace king

namespace knight {

/** lookup table for pseudo-legal moves of a knight */
class table {
  public:
    std::array<chester::engine::bitset, SQUARES> cells;

    table() : cells() {
        for (std::uint8_t i = 0; i < SQUARES; ++i) {
            const auto square = (class square)i;
            const auto file   = square.file();
            const auto rank   = square.rank();

            auto moves = bitset::empty();

            // . . . x .
            // . . . . .
            // . . N . .
            // . . . . .
            // . . . . .
            if (file < file::h and rank <=rank::six) {
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

} // namespace knight

} // namespace

template <>
auto chester::engine::lookup::moves<piece::king>(square square)
    -> chester::engine::bitset {
    static ::king::table table;
    return table.cells[square.raw];
}

template <>
auto chester::engine::lookup::moves<piece::knight>(square square)
    -> chester::engine::bitset {
    static ::knight::table table;
    return table.cells[square.raw];
}
