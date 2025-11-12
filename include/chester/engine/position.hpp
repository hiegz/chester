#pragma once

#include <chester/engine/bitboard.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/castling.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <cstddef>
#include <ostream>
#include <string>

// clang-format off

namespace chester::engine {

class position {
  public:
    constexpr position() = default;
    constexpr position(
        chester::engine::board board,
        chester::engine::side turn,
        chester::engine::castling castling,
        chester::engine::bitboard enpassant,
        std::size_t half_moves,
        std::size_t full_moves)
          : board(board),
            turn(turn),
            castling(castling),
            enpassant(enpassant),
            half_moves(half_moves),
            full_moves(full_moves)
    {}

    static auto traditional() -> position;

    chester::engine::board board;
    chester::engine::side turn;

    /**
     * Records each side's ability to castle.
     *
     * A situation that temporarily prevents castling does not affect this
     * property.
     */
    chester::engine::castling castling;

    /**
     * This is a square over which a pawn has just passed while moving two
     * squares. Represented as a bitboard with the en passant square set if
     * applicable, otherwise empty.
     *
     * This is recorded regardless of whether there is a
     * pawn in position to capture en passant.
     */
    chester::engine::bitboard enpassant;

    /**
     * The number of moves since the last capture or pawn advance used for the
     * fifty-move rule which states that a player can claim a draw if no capture
     * has been made and no pawn has been moved in the last fifty moves where a
     * move consists of a player completing a turn followed by the opponent
     * completing a turn.
     */
    std::size_t half_moves;

    /**
     * The number of the full moves. It starts at 1 and is incremented after
     * black's move.
     */
    std::size_t full_moves;
};

auto operator<<(std::ostream &os, position const &position) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::position const &position) -> std::string;
}
