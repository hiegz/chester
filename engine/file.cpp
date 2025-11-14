// clang-format off

#include <chester/engine/file.hpp>

#include <ostream>
#include <string>
#include <sstream>

auto chester::engine::operator<<(std::ostream &os, file f)
    -> std::ostream & {
    switch (f) {
        case file::a: return os << "a";
        case file::b: return os << "b";
        case file::c: return os << "c";
        case file::d: return os << "d";
        case file::e: return os << "e";
        case file::f: return os << "f";
        case file::g: return os << "g";
        case file::h: return os << "h";

        default:
            return os << "?";
    }
}

auto std::to_string(chester::engine::file file) -> std::string {
    std::ostringstream ss;
    ss << file;
    return ss.str();
}
