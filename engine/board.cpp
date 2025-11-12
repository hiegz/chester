#include <chester/engine/bitboard.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <algorithm>
#include <array>
#include <cctype>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

using chester::engine::board;
using chester::engine::piece;
using chester::engine::side;
using chester::engine::square;

// clang-format off

namespace {

constexpr auto format(side s, char ch) -> char {
    return (s == side::white) ? static_cast<char>(std::toupper(static_cast<unsigned char>(ch))) : ch;
}

constexpr auto format(side s, piece p) -> char {
    switch (p) {
        case piece::king:   return ::format(s, 'k');
        case piece::queen:  return ::format(s, 'q');
        case piece::rook:   return ::format(s, 'r');
        case piece::bishop: return ::format(s, 'b');
        case piece::knight: return ::format(s, 'n');
        case piece::pawn:   return ::format(s, 'p');
    }

    throw std::runtime_error("unreachable");
}

}

auto chester::engine::operator<<(std::ostream &os,
                                 board const  &board) -> std::ostream & {
    constexpr int SQUARES = 64;

    std::array<bool,  SQUARES> square_empty; // NOLINT
    std::array<side,  SQUARES> square_side;  // NOLINT
    std::array<piece, SQUARES> square_piece; // NOLINT

    std::ranges::fill(square_empty, true);

    // flatten out
    for (auto side : chester::engine::sides) {
        for (auto piece : chester::engine::pieces) {
            bitboard bitboard = board.get(side, piece);

            while (not bitboard.is_empty()) {
                const square square = bitboard.pop_front();
                const int    index  = square.value;

#ifdef DEBUG
                if (not square_empty[index]) {
                    throw std::runtime_error("piece collision");
                }
#endif

                 square_empty[index] = false;
                 square_side[index] = side;
                square_piece[index] = piece;
            }
        }
    }

    for (rank rank = rank::eight; rank > rank::low; --rank) {
        for (file file = file::a; file < file::high; ++file) {
            const square square(file, rank);
            const int index = square.value;

            os << (square_empty[index] ? '.' : ::format(square_side[index], square_piece[index]));

            if (file + 1 < file::high) {
                os << ' ';
            }
        }

        if (rank - 1 > rank::low) {
            os << '\n';
        }
    }

    return os;
}

auto std::to_string(chester::engine::board const &board) -> std::string {
    std::ostringstream ss;
    ss << board;
    return ss.str();
}
