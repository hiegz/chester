#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

#include <chester/engine/file.hpp>
#include <chester/engine/rank.hpp>

// clang-format off

namespace chester::engine {

class bitset;

class square {
  public:
    std::int8_t raw;

    constexpr square() = default;
    template <typename T>
    constexpr explicit square(T raw) : raw(static_cast<std::int8_t>(raw)) {}
    constexpr square(class file f, class rank r) : raw(static_cast<std::int8_t>((r * 8) + f)) {
#ifdef DEBUG
    if (invalid()) {
        throw std::runtime_error("unable to create a square from invalid file/rank");
    }
#endif // DEBUG
    }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    [[nodiscard]]
    constexpr auto file() const -> file {
#ifdef DEBUG
        if (invalid()) {
            throw std::runtime_error("unable to extract a file from invalid square");
        }
#endif // DEBUG
        return chester::engine::file(raw % 8);
    }

    [[nodiscard]]
    constexpr auto rank() const -> rank {
#ifdef DEBUG
        if (invalid()) {
            throw std::runtime_error("unable to extract a rank from invalid square");
        }
#endif // DEBUG
        return chester::engine::rank(raw / 8);
    }

    //

    static const square a1;
    static const square a2;
    static const square a3;
    static const square a4;
    static const square a5;
    static const square a6;
    static const square a7;
    static const square a8;
    static const square b1;
    static const square b2;
    static const square b3;
    static const square b4;
    static const square b5;
    static const square b6;
    static const square b7;
    static const square b8;
    static const square c1;
    static const square c2;
    static const square c3;
    static const square c4;
    static const square c5;
    static const square c6;
    static const square c7;
    static const square c8;
    static const square d1;
    static const square d2;
    static const square d3;
    static const square d4;
    static const square d5;
    static const square d6;
    static const square d7;
    static const square d8;
    static const square e1;
    static const square e2;
    static const square e3;
    static const square e4;
    static const square e5;
    static const square e6;
    static const square e7;
    static const square e8;
    static const square f1;
    static const square f2;
    static const square f3;
    static const square f4;
    static const square f5;
    static const square f6;
    static const square f7;
    static const square f8;
    static const square g1;
    static const square g2;
    static const square g3;
    static const square g4;
    static const square g5;
    static const square g6;
    static const square g7;
    static const square g8;
    static const square h1;
    static const square h2;
    static const square h3;
    static const square h4;
    static const square h5;
    static const square h6;
    static const square h7;
    static const square h8;
    static const square low;
    static const square high;
};

constexpr square square::a1   = square(0);
constexpr square square::a2   = square(8);
constexpr square square::a3   = square(16);
constexpr square square::a4   = square(24);
constexpr square square::a5   = square(32);
constexpr square square::a6   = square(40);
constexpr square square::a7   = square(48);
constexpr square square::a8   = square(56);
constexpr square square::b1   = square(1);
constexpr square square::b2   = square(9);
constexpr square square::b3   = square(17);
constexpr square square::b4   = square(25);
constexpr square square::b5   = square(33);
constexpr square square::b6   = square(41);
constexpr square square::b7   = square(49);
constexpr square square::b8   = square(57);
constexpr square square::c1   = square(2);
constexpr square square::c2   = square(10);
constexpr square square::c3   = square(18);
constexpr square square::c4   = square(26);
constexpr square square::c5   = square(34);
constexpr square square::c6   = square(42);
constexpr square square::c7   = square(50);
constexpr square square::c8   = square(58);
constexpr square square::d1   = square(3);
constexpr square square::d2   = square(11);
constexpr square square::d3   = square(19);
constexpr square square::d4   = square(27);
constexpr square square::d5   = square(35);
constexpr square square::d6   = square(43);
constexpr square square::d7   = square(51);
constexpr square square::d8   = square(59);
constexpr square square::e1   = square(4);
constexpr square square::e2   = square(12);
constexpr square square::e3   = square(20);
constexpr square square::e4   = square(28);
constexpr square square::e5   = square(36);
constexpr square square::e6   = square(44);
constexpr square square::e7   = square(52);
constexpr square square::e8   = square(60);
constexpr square square::f1   = square(5);
constexpr square square::f2   = square(13);
constexpr square square::f3   = square(21);
constexpr square square::f4   = square(29);
constexpr square square::f5   = square(37);
constexpr square square::f6   = square(45);
constexpr square square::f7   = square(53);
constexpr square square::f8   = square(61);
constexpr square square::g1   = square(6);
constexpr square square::g2   = square(14);
constexpr square square::g3   = square(22);
constexpr square square::g4   = square(30);
constexpr square square::g5   = square(38);
constexpr square square::g6   = square(46);
constexpr square square::g7   = square(54);
constexpr square square::g8   = square(62);
constexpr square square::h1   = square(7);
constexpr square square::h2   = square(15);
constexpr square square::h3   = square(23);
constexpr square square::h4   = square(31);
constexpr square square::h5   = square(39);
constexpr square square::h6   = square(47);
constexpr square square::h7   = square(55);
constexpr square square::h8   = square(63);
constexpr square square::low  = square(-1);
constexpr square square::high = square(64);

constexpr std::array<square, 64> squares =
    {square::a1, square::a2, square::a3, square::a4, square::a5, square::a6, square::a7, square::a8,
     square::b1, square::b2, square::b3, square::b4, square::b5, square::b6, square::b7, square::b8,
     square::c1, square::c2, square::c3, square::c4, square::c5, square::c6, square::c7, square::c8,
     square::d1, square::d2, square::d3, square::d4, square::d5, square::d6, square::d7, square::d8,
     square::e1, square::e2, square::e3, square::e4, square::e5, square::e6, square::e7, square::e8,
     square::f1, square::f2, square::f3, square::f4, square::f5, square::f6, square::f7, square::f8,
     square::g1, square::g2, square::g3, square::g4, square::g5, square::g6, square::g7, square::g8,
     square::h1, square::h2, square::h3, square::h4, square::h5, square::h6, square::h7, square::h8};

constexpr auto operator==(square a, square b) -> bool {
    return a.raw == b.raw;
}

constexpr auto operator!=(square a, square b) -> bool{
    return a.raw != b.raw;
}

constexpr auto operator<(square a, square b) -> bool{
    return a.raw < b.raw;
}

constexpr auto operator<=(square a, square b) -> bool {
    return a.raw <= b.raw;
}

constexpr auto operator>(square a, square b) -> bool {
    return a.raw > b.raw;
}

constexpr auto operator>=(square a, square b) -> bool {
    return a.raw >= b.raw;
}

template <typename T>
constexpr auto operator+(square a, T b) -> square requires(std::is_integral_v<T>) {
    return square(a.raw + b);
}

template <typename T>
constexpr auto operator>>(square a, T b) -> square requires(std::is_integral_v<T>) {
    return a + b;
}

template <typename T>
constexpr auto operator+=(square &a, T b) requires(std::is_integral_v<T>) {
    a = a + b;
}

template <typename T>
constexpr auto operator>>=(square &a, T b) requires(std::is_integral_v<T>) {
    a = a >> b;
}

// ++sq
constexpr auto operator++(square &sq) -> square & {
    sq += 1;
    return sq;
}

// sq++
constexpr auto operator++(square &sq, int) -> square {
    const square prev = sq;
    ++sq;
    return prev;
}

template <typename T>
constexpr auto operator-(square a, T b) -> square requires(std::is_integral_v<T>) {
    return square(a.raw - b);
}

template <typename T>
constexpr auto operator<<(square a, T b) -> square requires(std::is_integral_v<T>) {
    return a - b;
}

template <typename T>
constexpr auto operator-=(square &a, T b) requires(std::is_integral_v<T>) {
    a = a - b;
}

template <typename T>
constexpr auto operator<<=(square &a, T b) requires(std::is_integral_v<T>) {
    a = a << b;
}

// --sq
constexpr auto operator--(square &sq) -> square & {
    sq -= 1;
    return sq;
}

// sq--
constexpr auto operator--(square &sq, int) -> square {
    const square prev = sq;
    --sq;
    return prev;
}

constexpr auto square::valid() const -> bool {
    return *this > square::low and *this < square::high;
}

constexpr auto square::invalid() const -> bool {
    return not valid();
}

constexpr auto operator&(square a, square b) -> bitset;
constexpr auto operator|(square a, square b) -> bitset;
constexpr auto operator^(square a, square b) -> bitset;
constexpr auto operator~(square sq)          -> bitset;

auto operator<<(std::ostream &os, chester::engine::square sq) -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::square sq) -> std::string;
} // namespace std
