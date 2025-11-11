// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

enum class piece : std::uint8_t {
    king   = 0,
    queen  = 1,
    rook   = 2,
    bishop = 3,
    knight = 4,
    pawn   = 5,
};

auto operator<<(std::ostream &os, enum chester::engine::piece piece) -> std::ostream &;

}

namespace std {
auto to_string(enum chester::engine::piece piece) -> std::string;
}

// NOLINTEND
