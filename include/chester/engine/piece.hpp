// clang-format off
// NOLINTBEGIN

#pragma once

#include <array>
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

constexpr std::array<piece, 6> pieces = {piece::king, piece::queen, piece::rook, piece::bishop, piece::knight, piece::pawn};

auto operator<<(std::ostream &os, enum chester::engine::piece piece) -> std::ostream &;

}

namespace std {
auto to_string(enum chester::engine::piece piece) -> std::string;
}

// NOLINTEND
