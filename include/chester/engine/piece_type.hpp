#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

// clang-format off

namespace chester::engine {

enum class piece_type : std::uint8_t {
    king   = 0,
    queen  = 1,
    rook   = 2,
    bishop = 3,
    knight = 4,
    pawn   = 5,
};

static constexpr std::array<enum piece_type, 6> piece_types =
    {piece_type::king,
     piece_type::queen,
     piece_type::rook,
     piece_type::bishop,
     piece_type::knight,
     piece_type::pawn};

auto operator<<(std::ostream &os, enum piece_type type) -> std::ostream &;

}

namespace std {
auto to_string(enum chester::engine::piece_type type) -> std::string;
}
