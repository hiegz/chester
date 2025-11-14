#pragma once

#include <chester/engine/bitset.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

namespace chester::engine::lookup {

/**
 * TODO
 */
template <enum chester::engine::piece::type>
auto moves(chester::engine::square square) -> chester::engine::bitset;

/**
 * TODO
 */
template <enum chester::engine::piece::type>
auto moves(chester::engine::square square, chester::engine::bitset blockers)
    -> chester::engine::bitset;

/**
 * TODO
 */
auto in_between(chester::engine::square a, chester::engine::square b)
    -> chester::engine::bitset;

} // namespace chester::engine::lookup
