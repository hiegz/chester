#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

// clang-format off

namespace chester::engine {

class piece_type {
  public:
    std::int8_t raw;

    constexpr piece_type() = default;
    template <typename T>
    constexpr explicit piece_type(T raw) : raw(static_cast<std::uint8_t>(raw)) {}
    constexpr operator std::int8_t() const { return raw; }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    static const piece_type king;
    static const piece_type queen;
    static const piece_type rook;
    static const piece_type bishop;
    static const piece_type knight;
    static const piece_type pawn;
    static const piece_type none;
    static const piece_type low;
    static const piece_type high;
};

constexpr piece_type piece_type::queen  = piece_type(0);
constexpr piece_type piece_type::rook   = piece_type(1);
constexpr piece_type piece_type::bishop = piece_type(2);
constexpr piece_type piece_type::knight = piece_type(3);
constexpr piece_type piece_type::pawn   = piece_type(4);
constexpr piece_type piece_type::king   = piece_type(5);
constexpr piece_type piece_type::none   = piece_type(-1);
constexpr piece_type piece_type::low    = piece_type(-1);
constexpr piece_type piece_type::high   = piece_type(6);

static constexpr std::array<piece_type, 6> piece_types =
    {piece_type::queen,
     piece_type::rook,
     piece_type::bishop,
     piece_type::knight,
     piece_type::pawn,
     piece_type::king};

constexpr auto piece_type::valid() const -> bool {
    return raw > piece_type::low && raw < piece_type::high;
}

constexpr auto piece_type::invalid() const -> bool {
    return not valid();
}

auto operator<<(std::ostream &os, piece_type type) -> std::ostream &;

}

namespace std {
auto to_string(chester::engine::piece_type type) -> std::string;
}
