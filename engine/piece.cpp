// clang-format off

#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>

#include <ostream>
#include <string>
#include <sstream>
#include <stdexcept>

auto chester::engine::operator<<(std::ostream &os, enum chester::engine::piece::type type)
    -> std::ostream & {
    switch (type) {
        case piece::king:   return os << "king";
        case piece::queen:  return os << "queen";
        case piece::rook:   return os << "rook";
        case piece::bishop: return os << "bishop";
        case piece::knight: return os << "knight";
        case piece::pawn:   return os << "pawn";
    }

    throw std::runtime_error("what the hell are you trying to do?");
}

auto chester::engine::operator<<(std::ostream &os, chester::engine::piece piece) -> std::ostream & {
    return (os << piece.side << " " << piece.type);
}

auto std::to_string(enum chester::engine::piece::type type) -> std::string {
    std::ostringstream ss;
    ss << type;
    return ss.str();
}

auto std::to_string(chester::engine::piece piece) -> std::string {
    std::ostringstream ss;
    ss << piece;
    return ss.str();
}
