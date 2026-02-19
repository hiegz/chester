#pragma once

#include <chester/bitset.hpp>
#include <chester/piece_type.hpp>
#include <chester/square.hpp>

namespace chester::lookup {

/**
 * TODO
 */
template <chester::piece_type>
auto moves(chester::square square) -> chester::bitset;

/**
 * TODO
 */
template <chester::piece_type>
auto moves(chester::square square, chester::bitset blockers) -> chester::bitset;

/**
 * TODO
 */
auto in_between(chester::square a, chester::square b) -> chester::bitset;

} // namespace chester::lookup
