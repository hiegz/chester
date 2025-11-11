#pragma once

#include <array>
#include <cstdint>

namespace chester::engine {

enum class side : std::uint8_t {
    white = 0,
    black = 1,
};

constexpr std::array<side, 2> sides = {side::white, side::black};

} // namespace chester::engine
