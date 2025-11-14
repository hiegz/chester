#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

// clang-format off

namespace chester::engine {

class rank {
  public:
    std::int8_t raw;

    constexpr rank() = default;
    template <typename T>
    constexpr explicit rank(T raw) : raw(static_cast<std::int8_t>(raw)) {}
    constexpr operator std::int8_t() const { return raw; }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    static const rank one;
    static const rank two;
    static const rank three;
    static const rank four;
    static const rank five;
    static const rank six;
    static const rank seven;
    static const rank eight;
    static const rank low;
    static const rank high;
};

constexpr rank rank::one   = rank(0);
constexpr rank rank::two   = rank(1);
constexpr rank rank::three = rank(2);
constexpr rank rank::four  = rank(3);
constexpr rank rank::five  = rank(4);
constexpr rank rank::six   = rank(5);
constexpr rank rank::seven = rank(6);
constexpr rank rank::eight = rank(7);
constexpr rank rank::low   = rank(-1);
constexpr rank rank::high  = rank(8);

constexpr std::array<rank, 8> ranks =
    {rank::one, rank::two, rank::three, rank::four, rank::five, rank::six, rank::seven, rank::eight};

constexpr auto operator==(rank a, rank b) -> bool {
    return a.raw == b.raw;
}

constexpr auto operator!=(rank a, rank b) -> bool {
    return a.raw != b.raw;
}

constexpr auto operator<(rank a, rank b) -> bool {
    return a.raw <  b.raw;
}

constexpr auto operator<=(rank a, rank b) -> bool {
    return a.raw <= b.raw;
}

constexpr auto operator>(rank a, rank b) -> bool {
    return a.raw >  b.raw;
}

constexpr auto operator>=(rank a, rank b) -> bool {
    return a.raw >= b.raw;
}

template <typename T>
constexpr auto operator+(rank a, T b) -> rank requires (std::is_integral_v<T>) {
    return rank(a.raw + b);
}

template <typename T>
constexpr auto operator+=(rank &a, T b) requires(std::is_integral_v<T>) {
    a = a + b;
}

// ++r
constexpr auto operator++(rank &r) -> rank & {
    r += 1;
    return r;
}

// r++
constexpr auto operator++(rank &r, int) -> rank {
    const rank prev = r;
    ++r;
    return prev;
}

template <typename T>
constexpr auto operator-(rank a, T b) -> rank requires(std::is_integral_v<T>) {
    return rank(a.raw - b);
}

template <typename T>
constexpr auto operator-=(rank &a, T b) requires(std::is_integral_v<T>) {
    a = a - b;
}

// --r
constexpr auto operator--(rank &r) -> rank & {
    r -= 1;
    return r;
}

// r--
constexpr auto operator--(rank &r, int) -> rank {
    const rank prev = r;
    --r;
    return prev;
}

constexpr auto rank::valid() const -> bool {
    return *this > rank::low and *this < rank::high;
}

constexpr auto rank::invalid() const -> bool {
    return not valid();
}

auto operator<<(std::ostream &os, rank r)
    -> std::ostream &;

}

namespace std {
auto to_string(chester::engine::rank r)  -> std::string;
}
