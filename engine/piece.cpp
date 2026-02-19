// clang-format off

#include <chester/piece.hpp>

#include <ostream>
#include <string>
#include <sstream>

auto chester::operator<<(std::ostream &os, chester::piece piece) -> std::ostream & {
    return (os << piece.side() << " " << piece.type());
}

auto std::to_string(chester::piece piece) -> std::string {
    std::ostringstream ss;
    ss << piece;
    return ss.str();
}
