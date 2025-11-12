#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <chester/engine/side.hpp>

auto chester::engine::operator<<(std::ostream              &os,
                                 enum chester::engine::side side)
    -> std::ostream & {
    switch (side) {
        case side::white: return os << "white";
        case side::black: return os << "black";
    }

    throw std::runtime_error("unreachable");
}

auto std::to_string(enum chester::engine::side side) -> std::string {
    std::ostringstream ss;
    ss << side;
    return ss.str();
}
