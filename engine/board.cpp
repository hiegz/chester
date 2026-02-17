#include <chester/engine/bitset.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/piece_type.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <algorithm>
#include <cctype>
#include <ostream>
#include <sstream>
#include <string>

#ifdef DEBUG
#include <stdexcept>
#endif

using chester::engine::file;
using chester::engine::piece;
using chester::engine::piece_type;
using chester::engine::side;
using chester::engine::square;

// clang-format off

namespace {

constexpr auto format(piece_type type) -> char {
    switch (type) {
        case piece_type::king:   return 'k';
        case piece_type::queen:  return 'q';
        case piece_type::rook:   return 'r';
        case piece_type::bishop: return 'b';
        case piece_type::knight: return 'n';
        case piece_type::pawn:   return 'p';

        default:
            throw std::runtime_error("unreachable");
    }
}

constexpr auto format(piece piece) -> char {
    char chr = ::format(piece.type());
    chr =
        (piece.side() == side::white
             ? static_cast<char>(std::toupper(static_cast<unsigned char>(chr)))
             : chr);

    return chr;
}

} // namespace

// ***
//
// Piece-oriented board implementation.
//
// ***

auto chester::engine::board<piece>::empty() -> board {
    board b;
    std::ranges::fill(b.pieces, bitset::empty());
    return b;
}

auto chester::engine::board<piece>::traditional() -> board {
    auto board = board::empty();

    // white

    board[piece::white_rook]   |= (square::a1 | square::h1);
    board[piece::white_knight] |= (square::b1 | square::g1);
    board[piece::white_bishop] |= (square::c1 | square::f1);
    board[piece::white_king]   |=  square::e1;
    board[piece::white_queen]  |=  square::d1;

    for (file f = file::a; f < file::high; ++f) {
        board[piece::white_pawn] |= square(f, rank::two);
    }

    // black

    board[piece::black_rook]   |= (square::a8 | square::h8);
    board[piece::black_knight] |= (square::b8 | square::g8);
    board[piece::black_bishop] |= (square::c8 | square::f8);
    board[piece::black_king]   |=  square::e8;
    board[piece::black_queen]  |=  square::d8;

    for (file f = file::a; f < file::high; ++f) {
        board[piece::black_pawn] |= square(f, rank::seven);
    }

    return board;
}


chester::engine::board<piece>::board(board<square> const &board)
    : chester::engine::board<piece>::board(board::empty())
{
    for (const auto sq : squares) {
        (*this)[board[sq]] |= sq;
    }
}

auto chester::engine::operator<<(std::ostream &os, board<piece> const &board)
    -> std::ostream &
{
    return os << (chester::engine::board<square>)board;
}

auto std::to_string(chester::engine::board<piece> const &board) -> std::string {
    std::ostringstream ss;
    ss << board;
    return ss.str();
}

// ***
//
// Square-oriented board implementation.
//
// ***

auto chester::engine::board<square>::empty() -> board {
    board b;
    std::ranges::fill(b.squares, piece::none);
    return b;
}

auto chester::engine::board<square>::traditional() -> board {
    auto board = board::empty();

    board[square::a1] = piece::white_rook;
    board[square::b1] = piece::white_knight;
    board[square::c1] = piece::white_bishop;
    board[square::d1] = piece::white_queen;
    board[square::e1] = piece::white_king;
    board[square::f1] = piece::white_bishop;
    board[square::g1] = piece::white_knight;
    board[square::h1] = piece::white_rook;

    for (auto file : files) {
        board[square(file, rank::two)] = piece::white_pawn;
    }

    board[square::a8] = piece::black_rook;
    board[square::b8] = piece::black_knight;
    board[square::c8] = piece::black_bishop;
    board[square::d8] = piece::black_queen;
    board[square::e8] = piece::black_king;
    board[square::f8] = piece::black_bishop;
    board[square::g8] = piece::black_knight;
    board[square::h8] = piece::black_rook;

    for (auto file : files) {
        board[square(file, rank::seven)] = piece::black_pawn;
    }

    return board;
}

chester::engine::board<square>::board(board<piece> const &board)
    : chester::engine::board<square>::board(board::empty())
{
    for (auto piece : chester::engine::pieces) {
        auto bitset = board[piece];

        while (bitset != bitset::empty()) {
            const auto square = bitset.pop_front();
            const auto index  = square.raw;

#ifdef DEBUG
            if (squares[index] != piece::none) {
                throw std::runtime_error("piece collision");
            }
#endif

            squares[index] = piece;
        }
    }
}

auto chester::engine::operator<<(std::ostream &os, board<square> const &board)
    -> std::ostream &
{
    for (auto rank = rank::eight; rank > rank::low; --rank) {
        for (auto file = file::a; file < file::high; ++file) {
            const auto square = ::square(file, rank);
            const auto piece = board[square];
            os << (piece != piece::none ? ::format(piece) : '.');
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

auto std::to_string(chester::engine::board<square> const &board) -> std::string {
    std::ostringstream ss;
    ss << board;
    return ss.str();
}
