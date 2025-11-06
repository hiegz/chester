#pragma once

#include <chester/engine/bitboard.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

namespace chester::engine {

/**
 * TODO
 */
template <chester::engine::piece>
auto lookup(chester::engine::square square) -> chester::engine::bitboard;

/**
 * TODO
 */
template <chester::engine::piece>
auto lookup(chester::engine::square square, chester::engine::bitboard blockers)
    -> chester::engine::bitboard;

} // namespace chester::engine
