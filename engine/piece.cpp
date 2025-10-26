// clang-format off

#include <chester/engine/piece.hpp>

#include <format>
#include <ostream>

auto operator<<(std::ostream &os, enum chester::engine::piece::value const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}

auto operator<<(std::ostream &os, chester::engine::piece const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}
