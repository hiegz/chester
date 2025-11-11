// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

enum class piece : std::uint8_t {
    king,
    queen,
    rook,
    bishop,
    knight,
    pawn,
};

auto operator<<(std::ostream &os, enum chester::engine::piece piece) -> std::ostream &;

}

namespace std {
auto to_string(enum chester::engine::piece piece) -> std::string;
}

// NOLINTEND
