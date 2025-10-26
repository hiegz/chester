// clang-format off

#include <chester/engine/file.hpp>

#include <format>
#include <ostream>

auto operator<<(std::ostream &os, enum chester::engine::file::value const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}

auto operator<<(std::ostream &os, chester::engine::file const &value)
    -> std::ostream & {
    os << std::format("{}", value);
    return os;
}
