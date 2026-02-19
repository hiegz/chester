#include <chester/castling_type.hpp>

#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

using chester::castling_type;

// clang-format off

auto chester::operator<<(std::ostream &os, castling_type castling_type)
    -> std::ostream & {
    switch (castling_type) {
        case castling_type::kingside:  os << "kingside"; break;
        case castling_type::queenside: os << "queenside"; break;

        default:
            throw std::runtime_error("unreachable");
    }

    return os;
}

auto std::to_string(castling_type castling_type) -> std::string {
    std::ostringstream ss;
    ss << castling_type;
    return ss.str();
}
