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

        lo = 255,
        hi = 8,
    };

    // cppcheck-suppress noExplicitConstructor
    constexpr file(file::value value) : value(value) {}
    constexpr auto operator==(file other) const         { return value == other.value; }
    constexpr auto operator!=(file other) const         { return value != other.value; }
    constexpr auto operator< (file other) const         { return value <  other.value; }
    constexpr auto operator<=(file other) const         { return value <= other.value; }
    constexpr auto operator> (file other) const         { return value >  other.value; }
    constexpr auto operator>=(file other) const         { return value >= other.value; }
    constexpr auto operator+ (int  other) const -> file { return value +  other;       }
    constexpr auto operator- (int  other) const -> file { return value -  other;       }
    constexpr auto operator+=(int  other)               { *this = *this + other;       }
    constexpr auto operator-=(int  other)               { *this = *this - other;       }

    // ++file
    constexpr auto operator++() -> file& {
        *this += 1;
        return *this;
    }

    // file++
    constexpr auto operator++(int) -> file {
        const file prev = *this;
        *this += 1;
        return prev;
    }

    // --file
    constexpr auto operator--() -> file& {
        *this -= 1;
        return *this;
    }

    // file--
    constexpr auto operator--(int) -> file {
        const file prev = *this;
        *this -= 1;
        return prev;
    }

    enum file::value value;

  private:
    constexpr file(std::uint8_t value)
        : value((enum file::value)value) {}
};

auto operator<<(std::ostream &os, enum chester::engine::file::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::file        const &file)  -> std::ostream &;

}

namespace std {
auto to_string(     chester::engine::file        file)  -> std::string;
auto to_string(enum chester::engine::file::value value) -> std::string;
}

// NOLINTEND
