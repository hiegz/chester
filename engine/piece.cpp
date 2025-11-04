// clang-format off

#include <chester/engine/piece.hpp>

#include <ostream>
#include <string>
#include <sstream>
#include <stdexcept>

auto chester::engine::operator<<(std::ostream &os, enum chester::engine::piece::value const &value)
    -> std::ostream & {
    switch (value) {
        case chester::engine::piece::king:   return os << "king";
        case chester::engine::piece::queen:  return os << "queen";
        case chester::engine::piece::rook:   return os << "rook";
        case chester::engine::piece::bishop: return os << "bishop";
        case chester::engine::piece::knight: return os << "knight";
        case chester::engine::piece::pawn:   return os << "pawn";
    }

    throw std::runtime_error("what the hell are you trying to do?");
}

auto chester::engine::operator<<(std::ostream &os, chester::engine::piece const &piece)
    -> std::ostream & {
    return os << piece.value;
}

auto std::to_string(enum chester::engine::piece::value value) -> std::string {
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

auto std::to_string(chester::engine::piece piece) -> std::string {
    return std::to_string(piece.value);
}
