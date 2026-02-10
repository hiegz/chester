// clang-format off

#include <chester/engine/piece.hpp>

#include <ostream>
#include <string>
#include <sstream>

auto chester::engine::operator<<(std::ostream &os, chester::engine::piece piece) -> std::ostream & {
    return (os << piece.side() << " " << piece.type());
}

auto std::to_string(chester::engine::piece piece) -> std::string {
    std::ostringstream ss;
    ss << piece;
    return ss.str();
}
