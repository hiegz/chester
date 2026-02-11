#pragma once

#include <cstdint>
#include <ostream>
#include <string>

#include <chester/engine/piece_type.hpp>

// clang-format off

namespace chester::engine {

class move_type {
  public:
    std::uint16_t raw;

    constexpr move_type() = default;
    template <typename T>
    constexpr explicit move_type(T raw)
        : raw(static_cast<std::uint16_t>(raw)) {}
    constexpr operator std::uint16_t() const { return raw; }

    constexpr auto operator==(move_type other) const -> bool {
        return raw == other.raw;
    }

    constexpr auto operator!=(move_type other) const -> bool {
        return raw != other.raw;
    }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    //

    static const move_type normal;
    static const move_type promotion;
    static const move_type enpassant;
    static const move_type castling;
};

constexpr move_type move_type::normal    = move_type(0b00U << 14U);
constexpr move_type move_type::promotion = move_type(0b01U << 14U);
constexpr move_type move_type::enpassant = move_type(0b10U << 14U);
constexpr move_type move_type::castling  = move_type(0b11U << 14U);


[[nodiscard]]
constexpr auto move_type::valid() const -> bool {
    return (raw & ~(0b11U << 14U)) == 0; }

[[nodiscard]]
constexpr auto move_type::invalid() const -> bool {
    return not valid();
}

auto operator<<(std::ostream &os, move_type type) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::move_type type) -> std::string;
}
