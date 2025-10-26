// clang-format off

#include <chester/engine/rank.hpp>

#include <format>
#include <ostream>

auto operator<<(std::ostream &os, enum chester::engine::rank::value const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}

auto operator<<(std::ostream &os, chester::engine::rank const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}
