#include <chester/engine/square.hpp>

#include <ostream>
#include <sstream>
#include <string>

auto chester::engine::operator<<(std::ostream &os, square sq)
    -> std::ostream & {
    return (os << sq.file() << sq.rank());
}

auto std::to_string(chester::engine::square square) -> std::string {
    std::ostringstream ss;
    ss << square;
    return ss.str();
}
