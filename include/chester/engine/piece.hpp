// clang-format off
// NOLINTBEGIN

#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#include <chester/engine/side.hpp>

namespace chester::engine {

class piece {
  public:
    enum type : std::uint8_t {
        king   = 0,
        queen  = 1,
        rook   = 2,
        bishop = 3,
        knight = 4,
        pawn   = 5,
        none   = 6,
    };

    static constexpr std::array<enum piece::type, 6> types =
        {piece::king, piece::queen, piece::rook, piece::bishop, piece::knight, piece::pawn};

    constexpr piece() = default;

    constexpr piece(enum side side, enum type type)
        : side(side), type(type) {}

    enum side side;
    enum type type;
};


constexpr auto operator+(enum side side, enum piece::type type) -> piece {
    return piece(side, type);
}

constexpr std::array<piece, 12> pieces =
    {side::white + piece::king,
     side::white + piece::queen,
     side::white + piece::rook,
     side::white + piece::knight,
     side::white + piece::bishop,
     side::white + piece::pawn,
     side::black + piece::king,
     side::black + piece::queen,
     side::black + piece::rook,
     side::black + piece::knight,
     side::black + piece::bishop,
     side::black + piece::pawn};

auto operator<<(std::ostream &os, enum piece::type type)  -> std::ostream &;
auto operator<<(std::ostream &os,      piece       piece) -> std::ostream &;

}

namespace std {
auto to_string(enum chester::engine::piece::type type)  -> std::string;
auto to_string(     chester::engine::piece       piece) -> std::string;
}

// NOLINTEND
