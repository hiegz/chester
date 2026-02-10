#include <chester/engine/bitboard.hpp>
#include <chester/engine/bitset.hpp>
#include <chester/engine/castling.hpp>
#include <chester/engine/position.hpp>
#include <chester/engine/side.hpp>

#include <ostream>
#include <sstream>
#include <string>

auto chester::engine::position::traditional() -> position {
    position position;

    position.bitboard   = bitboard::traditional();
    position.turn       = side::white;
    position.castling   = castling::all;
    position.enpassant  = bitset::empty();
    position.half_moves = 0;
    position.full_moves = 1;

    return position;
}

auto chester::engine::operator<<(std::ostream                    &os,
                                 chester::engine::position const &position)
    -> std::ostream & {

    os << "board:\n";
    os << position.bitboard;
    os << "\n";
    os << "turn: " << position.turn << "\n";
    os << "castling: " << position.castling << "\n";
    os << "en passant: "
       << (position.enpassant == bitset::empty()
               ? "none"
               : std::to_string(position.enpassant.scan_forward()))
       << "\n";
    os << "half moves: " << position.half_moves << "\n";
    os << "full moves: " << position.full_moves;

    return os;
}

auto std::to_string(chester::engine::position const &position) -> std::string {
    std::ostringstream ss;
    ss << position;
    return ss.str();
}
