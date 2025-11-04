// clang-format off

#include <chester/engine/square.hpp>

#include <ostream>
#include <string>
#include <sstream>

auto chester::engine::operator<<(std::ostream &os, enum chester::engine::square::value const &value)
    -> std::ostream & {
    os << chester::engine::square(value);
    return os;
}

auto chester::engine::operator<<(std::ostream &os, chester::engine::square const &square)
    -> std::ostream & {
    return os << square.file() << square.rank();
}

auto std::to_string(chester::engine::square square) -> std::string {
    std::ostringstream ss;
    ss << square;
    return ss.str();
}

auto std::to_string(enum chester::engine::square::value value) -> std::string {
    return std::to_string(chester::engine::square(value));
}
