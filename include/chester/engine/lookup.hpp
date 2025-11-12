#pragma once

#include <chester/engine/bitboard.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

namespace chester::engine {

/**
 * TODO
 */
template <enum chester::engine::piece::type>
auto lookup(chester::engine::square square) -> chester::engine::bitboard;

/**
 * TODO
 */
template <enum chester::engine::piece::type>
auto lookup(chester::engine::square square, chester::engine::bitboard blockers)
    -> chester::engine::bitboard;

} // namespace chester::engine
