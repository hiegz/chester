#pragma once

#include <chester/board.hpp>
#include <chester/castling.hpp>
#include <chester/side.hpp>
#include <chester/square.hpp>

#include <cstddef>
#include <ostream>
#include <string>

// clang-format off

namespace chester {

template <typename Index>
class position {
  public:
    constexpr position() = default;
    constexpr position(
        chester::board<Index> const &board,
        chester::side turn,
        chester::castling castling,
        chester::square enpassant,
        size_t half_moves,
        size_t full_moves)
          : board(board),
            turn(turn),
            castling(castling),
            enpassant(enpassant),
            half_moves(half_moves),
            full_moves(full_moves)
    {}

    static auto traditional() -> position;

    constexpr auto operator==(position const &) const -> bool = default;
    constexpr auto operator!=(position const &) const -> bool = default;

    /**
     * Current piece placement on the board.
     */
    chester::board<Index> board;

    /**
     * Side to move.
     */
    chester::side turn;

    /**
     * Records each side's ability to castle.
     *
     * A situation that temporarily prevents castling does not affect this
     * property.
     */
    chester::castling castling;

    /**
     * This is a square over which a pawn has just passed while moving two
     * squares.
     *
     * This is recorded regardless of whether there is a
     * pawn in position to capture en passant.
     */
    chester::square enpassant;

    /**
     * The number of moves since the last capture or pawn advance used for the
     * fifty-move rule which states that a player can claim a draw if no capture
     * has been made and no pawn has been moved in the last fifty moves where a
     * move consists of a player completing a turn followed by the opponent
     * completing a turn.
     */
    size_t half_moves;

    /**
     * The number of the full moves. It starts at 1 and is incremented after
     * black's move.
     */
    size_t full_moves;
};

template <typename Index>
auto operator<<(std::ostream &os, position<Index> const &position) -> std::ostream &;

} // namespace chester::engine

namespace std {
template<typename Index>
auto to_string(chester::position<Index> const &position) -> std::string;
}
