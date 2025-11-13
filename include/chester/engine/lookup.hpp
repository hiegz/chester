#pragma once

#include <chester/engine/bitboard.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

namespace chester::engine::lookup {

/**
 * TODO
 */
template <enum chester::engine::piece::type>
auto moves(chester::engine::square square) -> chester::engine::bitboard;

/**
 * TODO
 */
template <enum chester::engine::piece::type>
auto moves(chester::engine::square square, chester::engine::bitboard blockers)
    -> chester::engine::bitboard;

} // namespace chester::engine::lookup
