#include <chester/engine/castling_type.hpp>

#include <ostream>
#include <sstream>
#include <string>

using chester::engine::castling_type;

auto chester::engine::operator<<(std::ostream &os, castling_type castling_type)
    -> std::ostream & {
    switch (castling_type) {
        case castling_type::kingside:  os << "kingside"; break;
        case castling_type::queenside: os << "queenside"; break;
    }

    return os;
}

auto std::to_string(castling_type castling_type) -> std::string {
    std::ostringstream ss;
    ss << castling_type;
    return ss.str();
}
