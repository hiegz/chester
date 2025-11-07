// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

class file {
  public:
    enum value : std::uint8_t {
        a = 0,
        b = 1,
        c = 2,
        d = 3,
        e = 4,
        f = 5,
        g = 6,
        h = 7,

        low  = 255, // (-1)
        high = 8,
    };

    constexpr file() : value(value::a) {}
    // cppcheck-suppress noExplicitConstructor
    constexpr file(file::value value) : value(value) {}

    enum file::value value;

  private:
    // cppcheck-suppress noExplicitConstructor
    constexpr file(std::uint8_t value)
        : value((enum file::value)value) {}
};

constexpr auto operator==(enum file::value lhs, enum file::value rhs) {
    return (std::int8_t)lhs == (std::int8_t)rhs;
}

constexpr auto operator!=(enum file::value lhs, enum file::value rhs) {
    return (std::int8_t)lhs != (std::int8_t)rhs;
}

constexpr auto operator<(enum file::value lhs, enum file::value rhs) {
    return (std::int8_t)lhs < (std::int8_t)rhs;
}

constexpr auto operator<=(enum file::value lhs, enum file::value rhs) {
    return (std::int8_t)lhs <= (std::int8_t)rhs;
}

constexpr auto operator>(enum file::value lhs, enum file::value rhs) {
    return (std::int8_t)lhs > (std::int8_t)rhs;
}

constexpr auto operator>=(enum file::value lhs, enum file::value rhs) {
    return (std::int8_t)lhs >= (std::int8_t)rhs;
}

constexpr auto operator+(enum file::value lhs, int rhs) -> enum file::value {
    return (enum file::value)((std::int8_t)lhs + rhs);
}

constexpr auto operator-(enum file::value lhs, int rhs) -> enum file::value {
    return (enum file::value)((std::int8_t)lhs - rhs);
}

constexpr auto operator+=(enum file::value &lhs, int rhs) {
    lhs = lhs + rhs;
}

constexpr auto operator-=(enum file::value &lhs, int rhs) {
    lhs = lhs - rhs;
}

// ++lhs
constexpr auto operator++(enum file::value &lhs) -> enum file::value & {
    lhs += 1;
    return lhs;
}

// lhs++
constexpr auto operator++(enum file::value &lhs, int) -> enum file::value {
    const enum file::value prev = lhs;
    ++lhs;
    return prev;
}

// --lhs
constexpr auto operator--(enum file::value &lhs) -> enum file::value & {
    lhs -= 1;
    return lhs;
}

// lhs--
constexpr auto operator--(enum file::value &lhs, int) -> enum file::value {
    const enum file::value prev = lhs;
    --lhs;
    return prev;
}

constexpr auto operator==(file lhs, file rhs) {
    return lhs.value == rhs.value;
}

constexpr auto operator!=(file lhs, file rhs) {
    return lhs.value != rhs.value;
}

constexpr auto operator<(file lhs, file rhs) {
    return lhs.value < rhs.value;
}

constexpr auto operator<=(file lhs, file rhs) {
    return lhs.value <= rhs.value;
}

constexpr auto operator>(file lhs, file rhs) {
    return lhs.value > rhs.value;
}

constexpr auto operator>=(file lhs, file rhs) {
    return lhs.value >= rhs.value;
}

constexpr auto operator+(file lhs, int rhs) -> file {
    return lhs.value + rhs;
}

constexpr auto operator-(file lhs, int rhs) -> file {
    return lhs.value - rhs;
}

constexpr auto operator+=(file &lhs, int rhs) {
    lhs.value += rhs;
}

constexpr auto operator-=(file &lhs, int rhs) {
    lhs.value -= rhs;
}

// ++file
constexpr auto operator++(file &lhs) -> file& {
    ++lhs.value;
    return lhs;
}

// file++
constexpr auto operator++(file &lhs, int) -> file {
    const file prev = lhs;
    ++lhs;
    return prev;
}

// --file
constexpr auto operator--(file &lhs) -> file& {
    --lhs.value;
    return lhs;
}

// file--
constexpr auto operator--(file &lhs, int) -> file {
    const file prev = lhs;
    --lhs;
    return prev;
}

auto operator<<(std::ostream &os, enum chester::engine::file::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::file        const &file)  -> std::ostream &;

}

namespace std {
auto to_string(     chester::engine::file        file)  -> std::string;
auto to_string(enum chester::engine::file::value value) -> std::string;
}

// NOLINTEND
