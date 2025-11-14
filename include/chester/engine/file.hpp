#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

// clang-format off

namespace chester::engine {

class file {
  public:
    std::int8_t raw;

    constexpr file() = default;
    template <typename T>
    constexpr explicit file(T raw) : raw(static_cast<std::int8_t>(raw)) {}
    constexpr operator std::int8_t() const { return raw; }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    static const file a;
    static const file b;
    static const file c;
    static const file d;
    static const file e;
    static const file f;
    static const file g;
    static const file h;
    static const file low;
    static const file high;
};

constexpr file file::a    = file(0);
constexpr file file::b    = file(1);
constexpr file file::c    = file(2);
constexpr file file::d    = file(3);
constexpr file file::e    = file(4);
constexpr file file::f    = file(5);
constexpr file file::g    = file(6);
constexpr file file::h    = file(7);
constexpr file file::low  = file(-1);
constexpr file file::high = file(8);

constexpr std::array<file, 8> files =
    {file::a, file::b, file::c, file::d, file::e, file::f, file::g, file::h};

constexpr auto operator==(file a, file b) -> bool {
    return a.raw == b.raw;
}

constexpr auto operator!=(file a, file b) -> bool {
    return a.raw != b.raw;
}

constexpr auto operator<(file a, file b) -> bool {
    return a.raw <  b.raw;
}

constexpr auto operator<=(file a, file b) -> bool {
    return a.raw <= b.raw;
}

constexpr auto operator>(file a, file b) -> bool {
    return a.raw >  b.raw;
}

constexpr auto operator>=(file a, file b) -> bool {
    return a.raw >= b.raw;
}

template <typename T>
constexpr auto operator+(file a, T b) -> file requires (std::is_integral_v<T>) {
    return file(a.raw + b);
}

template <typename T>
constexpr auto operator+=(file &a, T b) requires(std::is_integral_v<T>) {
    a = a + b;
}

// ++f
constexpr auto operator++(file &f) -> file & {
    f += 1;
    return f;
}

// f++
constexpr auto operator++(file &f, int) -> file {
    const file prev = f;
    ++f;
    return prev;
}

template <typename T>
constexpr auto operator-(file a, T b) -> file requires(std::is_integral_v<T>) {
    return file(a.raw - b);
}

template <typename T>
constexpr auto operator-=(file &a, T b) requires(std::is_integral_v<T>) {
    a = a - b;
}

// --f
constexpr auto operator--(file &f) -> file & {
    f -= 1;
    return f;
}

// f--
constexpr auto operator--(file &f, int) -> file {
    const file prev = f;
    --f;
    return prev;
}

constexpr auto file::valid() const -> bool {
    return *this > file::low and *this < file::high;
}

constexpr auto file::invalid() const -> bool {
    return not valid();
}

auto operator<<(std::ostream &os, file f)
    -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::file file) -> std::string;
} // namespace std
