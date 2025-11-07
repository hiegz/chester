// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace chester::engine {

class rank {
  public:
    enum value : std::uint8_t {
        one   = 0,
        two   = 1,
        three = 2,
        four  = 3,
        five  = 4,
        six   = 5,
        seven = 6,
        eight = 7,

        low  = 255, // (-1)
        high = 8,
    };

    constexpr rank() : value(value::one) {}
    // cppcheck-suppress noExplicitConstructor
    constexpr rank(rank::value value) : value(value) {}

    enum rank::value value;

  private:
    constexpr rank(std::uint8_t value)
        : value((enum rank::value)value) {}
};

constexpr auto operator==(enum rank::value lhs, enum rank::value rhs) {
    return (std::int8_t)lhs == (std::int8_t)rhs;
}

constexpr auto operator!=(enum rank::value lhs, enum rank::value rhs) {
    return (std::int8_t)lhs != (std::int8_t)rhs;
}

constexpr auto operator<(enum rank::value lhs, enum rank::value rhs) {
    return (std::int8_t)lhs < (std::int8_t)rhs;
}

constexpr auto operator<=(enum rank::value lhs, enum rank::value rhs) {
    return (std::int8_t)lhs <= (std::int8_t)rhs;
}

constexpr auto operator>(enum rank::value lhs, enum rank::value rhs) {
    return (std::int8_t)lhs > (std::int8_t)rhs;
}

constexpr auto operator>=(enum rank::value lhs, enum rank::value rhs) {
    return (std::int8_t)lhs >= (std::int8_t)rhs;
}

constexpr auto operator+(enum rank::value lhs, int rhs) -> enum rank::value {
    return (enum rank::value)((std::int8_t)lhs + rhs);
}

constexpr auto operator-(enum rank::value lhs, int rhs) -> enum rank::value {
    return (enum rank::value)((std::int8_t)lhs - rhs);
}

constexpr auto operator+=(enum rank::value &lhs, int rhs) {
    lhs = lhs + rhs;
}

constexpr auto operator-=(enum rank::value &lhs, int rhs) {
    lhs = lhs - rhs;
}

// ++lhs
constexpr auto operator++(enum rank::value &lhs) -> enum rank::value & {
    lhs += 1;
    return lhs;
}

// lhs++
constexpr auto operator++(enum rank::value &lhs, int) -> enum rank::value {
    const enum rank::value prev = lhs;
    ++lhs;
    return prev;
}

// --lhs
constexpr auto operator--(enum rank::value &lhs) -> enum rank::value & {
    lhs -= 1;
    return lhs;
}

// lhs--
constexpr auto operator--(enum rank::value &lhs, int) -> enum rank::value {
    const enum rank::value prev = lhs;
    --lhs;
    return prev;
}

constexpr auto operator==(rank lhs, rank rhs) {
    return lhs.value == rhs.value;
}

constexpr auto operator!=(rank lhs, rank rhs) {
    return lhs.value != rhs.value;
}

constexpr auto operator<(rank lhs, rank rhs) {
    return lhs.value < rhs.value;
}

constexpr auto operator<=(rank lhs, rank rhs) {
    return lhs.value <= rhs.value;
}

constexpr auto operator>(rank lhs, rank rhs) {
    return lhs.value > rhs.value;
}

constexpr auto operator>=(rank lhs, rank rhs) {
    return lhs.value >= rhs.value;
}

constexpr auto operator+(rank lhs, int rhs) -> rank {
    return lhs.value + rhs;
}

constexpr auto operator-(rank lhs, int rhs) -> rank {
    return lhs.value - rhs;
}

constexpr auto operator+=(rank &lhs, int rhs) {
    lhs.value += rhs;
}

constexpr auto operator-=(rank &lhs, int rhs) {
    lhs.value -= rhs;
}

// ++rank
constexpr auto operator++(rank &lhs) -> rank& {
    ++lhs.value;
    return lhs;
}

// rank++
constexpr auto operator++(rank &lhs, int) -> rank {
    const rank prev = lhs;
    ++lhs;
    return prev;
}

// --rank
constexpr auto operator--(rank &lhs) -> rank& {
    --lhs.value;
    return lhs;
}

// rank--
constexpr auto operator--(rank &lhs, int) -> rank {
    const rank prev = lhs;
    --lhs;
    return prev;
}

auto operator<<(std::ostream &os, enum chester::engine::rank::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::rank        const &rank)  -> std::ostream &;

}

namespace std {
auto to_string(     chester::engine::rank        rank)  -> std::string;
auto to_string(enum chester::engine::rank::value value) -> std::string;
}

// NOLINTEND
