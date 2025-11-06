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

        lo = 255,
        hi = 8,
    };

    constexpr rank() : value(value::one) {}
    // cppcheck-suppress noExplicitConstructor
    constexpr rank(rank::value value) : value(value) {}
    constexpr auto operator==(rank other) const         { return value == other.value; }
    constexpr auto operator!=(rank other) const         { return value != other.value; }
    constexpr auto operator< (rank other) const         { return value <  other.value; }
    constexpr auto operator<=(rank other) const         { return value <= other.value; }
    constexpr auto operator> (rank other) const         { return value >  other.value; }
    constexpr auto operator>=(rank other) const         { return value >= other.value; }
    constexpr auto operator+ (int  other) const -> rank { return value +  other;       }
    constexpr auto operator- (int  other) const -> rank { return value -  other;       }
    constexpr auto operator+=(int  other)               { *this = *this + other;       }
    constexpr auto operator-=(int  other)               { *this = *this - other;       }

    // ++rank
    constexpr auto operator++() -> rank& {
        *this += 1;
        return *this;
    }

    // rank++
    constexpr auto operator++(int) -> rank {
        const rank prev = *this;
        *this += 1;
        return prev;
    }

    // --rank
    constexpr auto operator--() -> rank& {
        *this -= 1;
        return *this;
    }

    // rank--
    constexpr auto operator--(int) -> rank {
        const rank prev = *this;
        *this -= 1;
        return prev;
    }

    enum rank::value value;

  private:
    constexpr rank(std::uint8_t value)
        : value((enum rank::value)value) {}
};

auto operator<<(std::ostream &os, enum chester::engine::rank::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::rank        const &rank)  -> std::ostream &;

}

namespace std {
auto to_string(     chester::engine::rank        rank)  -> std::string;
auto to_string(enum chester::engine::rank::value value) -> std::string;
}

// NOLINTEND
