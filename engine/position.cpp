#include <chester/bitset.hpp>
#include <chester/board.hpp>
#include <chester/castling.hpp>
#include <chester/piece.hpp>
#include <chester/position.hpp>
#include <chester/side.hpp>
#include <chester/square.hpp>

#include <ostream>
#include <sstream>
#include <string>

using chester::piece;
using chester::square;

// clang-format off

template <typename Index>
auto chester::position<Index>::traditional() -> position {
    position position;

    position.board      = chester::board<Index>::traditional();
    position.turn       = side::white;
    position.castling   = castling::all;
    position.enpassant  = square::none;
    position.half_moves = 0;
    position.full_moves = 1;

    return position;
}

template auto chester::position <piece>::traditional() -> position;
template auto chester::position<square>::traditional() -> position;

template <typename Index>
auto chester::operator<<(std::ostream &os, position<Index> const &position)
    -> std::ostream & {

    os << "board:\n";
    os << position.board;
    os << "\n";
    os << "turn: " << position.turn << "\n";
    os << "castling: " << position.castling << "\n";
    os << "en passant: "
       << (position.enpassant == square::none
               ? "none"
               : std::to_string(bitset(position.enpassant).scan_forward()))
       << "\n";
    os << "half moves: " << position.half_moves << "\n";
    os << "full moves: " << position.full_moves;

    return os;
}

template auto chester::operator<<<piece> (std::ostream &os, position<piece>  const &position) -> std::ostream &;
template auto chester::operator<<<square>(std::ostream &os, position<square> const &position) -> std::ostream &;

template <typename Index>
auto std::to_string(chester::position<Index> const &position) -> std::string {
    std::ostringstream ss;
    ss << position;
    return ss.str();
}

template auto std::to_string<piece> (chester::position<piece>  const &position) -> std::string;
template auto std::to_string<square>(chester::position<square> const &position) -> std::string;
