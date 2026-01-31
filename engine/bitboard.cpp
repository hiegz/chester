#include <chester/engine/bitboard.hpp>
#include <chester/engine/bitset.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/piece_type.hpp>
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

using chester::engine::bitboard;
using chester::engine::piece;
using chester::engine::piece_type;
using chester::engine::side;
using chester::engine::square;

// clang-format off

auto bitboard::traditional() -> bitboard {
    bitboard bitboard = bitboard::empty();

    // white

    bitboard[piece::white_rook]   |= (square::a1 | square::h1);
    bitboard[piece::white_knight] |= (square::b1 | square::g1);
    bitboard[piece::white_bishop] |= (square::c1 | square::f1);
    bitboard[piece::white_king]   |=  square::e1;
    bitboard[piece::white_queen]  |=  square::d1;

    for (file f = file::a; f < file::high; ++f) {
        bitboard[piece::white_pawn] |= square(f, rank::two);
    }

    // black

    bitboard[piece::black_rook]   |= (square::a8 | square::h8);
    bitboard[piece::black_knight] |= (square::b8 | square::g8);
    bitboard[piece::black_bishop] |= (square::c8 | square::f8);
    bitboard[piece::black_king]   |=  square::e8;
    bitboard[piece::black_queen]  |=  square::d8;

    for (file f = file::a; f < file::high; ++f) {
        bitboard[piece::black_pawn] |= square(f, rank::seven);
    }

    return bitboard;
}

namespace {

constexpr auto format(enum piece_type type) -> char {
    switch (type) {
        case piece_type::king:   return 'k';
        case piece_type::queen:  return 'q';
        case piece_type::rook:   return 'r';
        case piece_type::bishop: return 'b';
        case piece_type::knight: return 'n';
        case piece_type::pawn:   return 'p';
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
                                 bitboard const  &bitboard) -> std::ostream & {
    constexpr int SQUARES = 64;

    std::array<bool,  SQUARES> square_empty; // NOLINT
    std::array<piece, SQUARES> square_piece; // NOLINT

    std::ranges::fill(square_empty, true);

    // flatten out
    for (auto piece : chester::engine::pieces) {
        bitset bitset = bitboard[piece];

        while (bitset != bitset::empty()) {
            const square square = bitset.pop_front();
            const char   index  = square.raw;

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
            const char   index = square.raw;

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

auto std::to_string(chester::engine::bitboard const &bitboard) -> std::string {
    std::ostringstream ss;
    ss << bitboard;
    return ss.str();
}
