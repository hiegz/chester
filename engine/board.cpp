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

auto board::traditional() -> board {
    board board = board::empty();

    // white

    board[side::white + piece::rook]   |= (square::a1 | square::h1);
    board[side::white + piece::knight] |= (square::b1 | square::g1);
    board[side::white + piece::bishop] |= (square::c1 | square::f1);
    board[side::white + piece::king]   |=  square::d1;
    board[side::white + piece::queen]  |=  square::e1;

    for (file f = file::a; f < file::high; ++f) {
        board[side::white + piece::pawn] |= square(f, rank::two);
    }

    // black

    board[side::black + piece::rook]   |= (square::a8 | square::h8);
    board[side::black + piece::knight] |= (square::b8 | square::g8);
    board[side::black + piece::bishop] |= (square::c8 | square::f8);
    board[side::black + piece::king]   |=  square::d8;
    board[side::black + piece::queen]  |=  square::e8;

    for (file f = file::a; f < file::high; ++f) {
        board[side::black + piece::pawn] |= square(f, rank::seven);
    }

    return board;
}

namespace {

constexpr auto format(enum piece::type type) -> char {
    switch (type) {
        case piece::king:   return 'k';
        case piece::queen:  return 'q';
        case piece::rook:   return 'r';
        case piece::bishop: return 'b';
        case piece::knight: return 'n';
        case piece::pawn:   return 'p';
    }

    throw std::runtime_error("unreachable");
}

constexpr auto format(piece piece) -> char {
    char chr = ::format(piece.type);
    chr = (piece.side == side::white ? static_cast<char>(std::toupper(static_cast<unsigned char>(chr))) : chr);

    return chr;
}

}

auto chester::engine::operator<<(std::ostream &os,
                                 board const  &board) -> std::ostream & {
    constexpr int SQUARES = 64;

    std::array<bool,  SQUARES> square_empty; // NOLINT
    std::array<piece, SQUARES> square_piece; // NOLINT

    std::ranges::fill(square_empty, true);

    // flatten out
    for (auto piece : chester::engine::pieces) {
        bitboard bitboard = board[piece];

        while (not bitboard.is_empty()) {
            const square square = bitboard.pop_front();
            const int    index  = square.value;

#ifdef DEBUG
            if (not square_empty[index]) {
                throw std::runtime_error("piece collision");
            }
#endif

            square_empty[index] = false;
            square_piece[index] = piece;
        }
    }

    for (rank rank = rank::eight; rank > rank::low; --rank) {
        for (file file = file::a; file < file::high; ++file) {
            const square square(file, rank);
            const int index = square.value;

            os << (square_empty[index] ? '.' : ::format(square_piece[index]));

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
