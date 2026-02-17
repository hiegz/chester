#include <chester/engine/bitset.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/castling.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/position.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <ostream>
#include <sstream>
#include <string>

using chester::engine::piece;
using chester::engine::square;

// clang-format off

template <typename Index>
auto chester::engine::position<Index>::traditional() -> position {
    position position;

    position.board      = chester::engine::board<Index>::traditional();
    position.turn       = side::white;
    position.castling   = castling::all;
    position.enpassant  = square::none;
    position.half_moves = 0;
    position.full_moves = 1;

    return position;
}

template auto chester::engine::position <piece>::traditional() -> position;
template auto chester::engine::position<square>::traditional() -> position;

template <typename Index>
auto chester::engine::operator<<(std::ostream &os, position<Index> const &position)
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

template auto chester::engine::operator<<<piece> (std::ostream &os, position<piece>  const &position) -> std::ostream &;
template auto chester::engine::operator<<<square>(std::ostream &os, position<square> const &position) -> std::ostream &;

template <typename Index>
auto std::to_string(chester::engine::position<Index> const &position) -> std::string {
    std::ostringstream ss;
    ss << position;
    return ss.str();
}

template auto std::to_string<piece> (chester::engine::position<piece>  const &position) -> std::string;
template auto std::to_string<square>(chester::engine::position<square> const &position) -> std::string;
