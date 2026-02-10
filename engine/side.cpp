#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <chester/engine/side.hpp>

// clang-format off

auto chester::engine::operator<<(std::ostream &os, chester::engine::side side)
    -> std::ostream & {
    switch (side) {
        case side::white: return os << "white";
        case side::black: return os << "black";

        default:
            throw std::runtime_error("unreachable");
    }
}

auto std::to_string(chester::engine::side side) -> std::string {
    std::ostringstream ss;
    ss << side;
    return ss.str();
}
