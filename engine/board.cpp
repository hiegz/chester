#include <chester/engine/bitboard.hpp>
#include <chester/engine/bitset.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/piece_type.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

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
using chester::engine::rank;
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

chester::engine::board::board(chester::engine::bitboard const &bitboard)
    : chester::engine::board(board::empty()) {
    for (auto piece : chester::engine::pieces) {
        bitset bitset = bitboard[piece];

        while (bitset != bitset::empty()) {
            const square square = bitset.pop_front();
            const char   index  = square.raw;

#ifdef DEBUG
            if (squares[index] != piece::none) {
                throw std::runtime_error("piece collision");
            }
#endif

            squares[index] = piece;
        }
    }
}

auto chester::engine::operator<<(std::ostream &os, chester::engine::board const &board)
    -> std::ostream & {
    for (rank rank = rank::eight; rank > rank::low; --rank) {
        for (file file = file::a; file < file::high; ++file) {
            const square square(file, rank);
            const auto   piece = board[square];
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

auto std::to_string(chester::engine::board const &board) -> std::string {
    std::ostringstream ss;
    ss << board;
    return ss.str();
}
