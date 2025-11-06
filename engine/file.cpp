// clang-format off

#include <chester/engine/file.hpp>

#include <ostream>
#include <string>
#include <sstream>

auto chester::engine::operator<<(std::ostream &os, enum chester::engine::file::value const &value)
    -> std::ostream & {
    switch (value) {
        case file::a: return os << "a";
        case file::b: return os << "b";
        case file::c: return os << "c";
        case file::d: return os << "d";
        case file::e: return os << "e";
        case file::f: return os << "f";
        case file::g: return os << "g";
        case file::h: return os << "h";

        default:      return os << "?";
    }
}

auto chester::engine::operator<<(std::ostream &os, chester::engine::file const &file)
    -> std::ostream & {
    return os << file.value;
}

auto std::to_string(chester::engine::file file) -> std::string {
    std::ostringstream ss;
    ss << file;
    return ss.str();
}

auto std::to_string(enum chester::engine::file::value value) -> std::string {
    return std::to_string(chester::engine::file(value));
}
