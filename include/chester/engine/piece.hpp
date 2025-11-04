// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

class piece {
  public:
    enum value : std::uint8_t {
        king,
        queen,
        rook,
        bishop,
        knight,
        pawn,
    };

    // cppcheck-suppress noExplicitConstructor
    constexpr piece(piece::value value) : value(value) {}
    constexpr auto operator==(piece other) const { return value == other.value; }
    constexpr auto operator!=(piece other) const { return value != other.value; }

    enum piece::value value;
};

auto operator<<(std::ostream &os, enum chester::engine::piece::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::piece        const &piece) -> std::ostream &;

}

namespace std {
auto to_string(enum chester::engine::piece::value value) -> std::string;
auto to_string(     chester::engine::piece        piece) -> std::string;
}

// NOLINTEND
