#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

enum class side : std::uint8_t {
    white = 0,
    black = 1,
};

constexpr std::array<side, 2> sides = {side::white, side::black};

auto operator<<(std::ostream &os, enum side side) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(enum chester::engine::side side) -> std::string;
}
