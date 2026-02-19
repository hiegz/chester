#include <chester/square.hpp>

#include <ostream>
#include <sstream>
#include <string>

auto chester::operator<<(std::ostream &os, square sq) -> std::ostream & {
    return (os << sq.file() << sq.rank());
}

auto std::to_string(chester::square square) -> std::string {
    std::ostringstream ss;
    ss << square;
    return ss.str();
}
