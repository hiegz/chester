#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

// clang-format off

enum class castling_type : std::uint8_t {
    kingside  = 0,
    queenside = 1,
};

constexpr std::array<castling_type, 2> castling_types =
    { castling_type::kingside, castling_type::queenside };

auto operator<<(std::ostream &os, castling_type castling_type) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::castling_type castling_type) -> std::string;
}
