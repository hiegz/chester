// clang-format off

#include <chester/piece_type.hpp>

#include <ostream>
#include <string>
#include <sstream>
#include <stdexcept>

auto chester::operator<<(std::ostream &os, chester::piece_type type)
    -> std::ostream & {
    switch (type) {
        case piece_type::king:   return os << "king";
        case piece_type::queen:  return os << "queen";
        case piece_type::rook:   return os << "rook";
        case piece_type::bishop: return os << "bishop";
        case piece_type::knight: return os << "knight";
        case piece_type::pawn:   return os << "pawn";

        default:
            throw std::runtime_error("what are you trying to do?");
    }
}

auto std::to_string(chester::piece_type type) -> std::string {
    std::ostringstream ss;
    ss << type;
    return ss.str();
}
