#include <array>

#include <chester/bitset.hpp>
#include <chester/file.hpp>
#include <chester/lookup.hpp>
#include <chester/rank.hpp>
#include <chester/square.hpp>

using chester::bitset;
using chester::file;
using chester::rank;
using chester::square;

// clang-format off

namespace {

template <unsigned int Angle>
auto ray(square origin) -> bitset;

template <>
auto ray<0>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();

    for (auto r = rank + 1; r < rank::high; ++r) {
        result |= square(file, r);
    }

    return result;
}

template <>
auto ray<45>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();
    class rank r;
    class file f;

    for (f = file + 1, r = rank + 1; f < file::high and r < rank::high; ++f, ++r) {
        result |= square(f, r);
    }

    return result;
}

template <>
auto ray<90>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();

    for (auto f = file + 1; f < file::high; ++f) {
        result |= square(f, rank);
    }

    return result;
}

template <>
auto ray<135>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();
    class file f;
    class rank r;

    for (f = file + 1, r = rank - 1; r > rank::low and f < file::high; --r, ++f) {
        result |= square(f, r);
    }


    return result;
}

template <>
auto ray<180>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();

    for (auto r = rank - 1; r > rank::low; --r) {
        result |= square(file, r);
    }

    return result;
}

template <>
auto ray<225>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();
    class rank r;
    class file f;

    for (f = file - 1, r = rank - 1; f > file::low and r > rank::low; --f, --r) {
        result |= square(f, r);
    }

    return result;
}

template <>
auto ray<270>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();

    for (auto f = file - 1; f > file::low; --f) {
        result |= square(f, rank);
    }

    return result;
}

template <>
auto ray<315>(square origin) -> bitset {
    const rank rank = origin.rank();
    const file file = origin.file();
    bitset result = bitset::empty();
    class rank r;
    class file f;

    for (f = file - 1, r = rank + 1; f > file::low and r < rank::high; --f, ++r) {
        result |= square(f, r);
    }

    return result;
}

class table {
  public:
    std::array<bitset, 64UL * 64UL> cells;

    table() : cells() {
        for (auto i = square::a1; i < square::high; ++i) {
            for (auto j = square::a1; j < square::high; ++j) {
                cells[(i.raw * 64) + j.raw] =
                    (::ray<  0>(i) & ::ray<  0 + 180>(j)) |
                    (::ray< 45>(i) & ::ray< 45 + 180>(j)) |
                    (::ray< 90>(i) & ::ray< 90 + 180>(j)) |
                    (::ray<135>(i) & ::ray<135 + 180>(j)) |
                    (::ray<  0>(j) & ::ray<  0 + 180>(i)) |
                    (::ray< 45>(j) & ::ray< 45 + 180>(i)) |
                    (::ray< 90>(j) & ::ray< 90 + 180>(i)) |
                    (::ray<135>(j) & ::ray<135 + 180>(i));
            }
        }
    }
};

} // namespace

auto chester::lookup::in_between(square a, square b) -> bitset {
    static ::table table;
    return table.cells[(a.raw * 64) + b.raw];
}
