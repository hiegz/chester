#include <chester/engine/bitboard.hpp>
#include <chester/engine/bitset.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/square.hpp>

#include <ostream>
#include <sstream>
#include <string>

using chester::engine::bitboard;
using chester::engine::board;
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

auto chester::engine::operator<<(std::ostream &os,
                                 bitboard const  &bitboard) -> std::ostream & {
    return os << (board)bitboard;
}

auto std::to_string(chester::engine::bitboard const &bitboard) -> std::string {
    std::ostringstream ss;
    ss << bitboard;
    return ss.str();
}
