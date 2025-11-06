// clang-format off

#include <chester/engine/rank.hpp>

#include <ostream>
#include <string>
#include <sstream>

auto chester::engine::operator<<(std::ostream &os, enum chester::engine::rank::value const &value)
    -> std::ostream & {
    switch (value) {
        case rank::one:   return os << "1";
        case rank::two:   return os << "2";
        case rank::three: return os << "3";
        case rank::four:  return os << "4";
        case rank::five:  return os << "5";
        case rank::six:   return os << "6";
        case rank::seven: return os << "7";
        case rank::eight: return os << "8";

        default:          return os << "?";
    }
}

auto chester::engine::operator<<(std::ostream &os, chester::engine::rank const &rank)
    -> std::ostream & {
    return os << rank.value;
}

auto std::to_string(chester::engine::rank rank) -> std::string {
    std::ostringstream ss;
    ss << rank;
    return ss.str();
}

auto std::to_string(enum chester::engine::rank::value value) -> std::string {
    return std::to_string(chester::engine::rank(value));
}
