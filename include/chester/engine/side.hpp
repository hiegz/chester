#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

namespace chester::engine {

// clang-format off

class side {
  public:
    std::int8_t raw;

    constexpr side() = default;
    template <typename T>
    constexpr explicit side(T raw) : raw(static_cast<std::uint8_t>(raw)) {}
    constexpr operator std::int8_t() const { return raw; }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    static const side white;
    static const side black;
    static const side none;
    static const side low;
    static const side high;
    static const side all;
};

constexpr side side::white = side(0);
constexpr side side::black = side(1);
constexpr side side::none  = side(-1);
constexpr side side::low   = side(-1);
constexpr side side::high  = side(2);
constexpr side side::all   = side(2);

constexpr std::array<side, 2> sides = {side::white, side::black};

constexpr auto side::valid() const -> bool {
    return raw == side::white || raw == side::black;
}

constexpr auto side::invalid() const -> bool {
    return not valid();
}

constexpr auto operator!(side side) -> class side {
#ifdef DEBUG
    if (side.invalid()) {
        throw std::runtime_error("side is invalid");
    }
#endif // DEBUG

    return chester::engine::side(!static_cast<bool>(side.raw));
}

auto operator<<(std::ostream &os, side side) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::side side) -> std::string;
}
