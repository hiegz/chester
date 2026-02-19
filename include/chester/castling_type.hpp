#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

namespace chester {

// clang-format off

class castling_type {
  public:
    std::int8_t raw;

    constexpr castling_type() = default;
    template <typename T>
    constexpr explicit castling_type(T raw) : raw(static_cast<std::uint8_t>(raw)) {}
    constexpr operator std::int8_t() const { return raw; }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    static const castling_type kingside;
    static const castling_type queenside;
    static const castling_type none;
    static const castling_type low;
    static const castling_type high;
};

constexpr castling_type castling_type::kingside  = castling_type(0);
constexpr castling_type castling_type::queenside = castling_type(1);
constexpr castling_type castling_type::none      = castling_type(-1);
constexpr castling_type castling_type::low       = castling_type(-1);
constexpr castling_type castling_type::high      = castling_type(2);

constexpr auto castling_type::valid() const -> bool {
    return *this == castling_type::kingside || *this == castling_type::queenside;
}

constexpr auto castling_type::invalid() const -> bool {
    return not valid();
}

constexpr std::array<castling_type, 2> castling_types =
    { castling_type::kingside, castling_type::queenside };

auto operator<<(std::ostream &os, castling_type castling_type) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::castling_type castling_type) -> std::string;
}
