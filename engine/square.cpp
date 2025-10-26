// clang-format off

#include <chester/engine/square.hpp>

#include <format>
#include <ostream>

auto operator<<(std::ostream &os, enum chester::engine::square::value const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}

auto operator<<(std::ostream &os, chester::engine::square const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}
