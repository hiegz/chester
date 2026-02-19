// clang-format off

#include <array>

#include <cstddef>
#include <cstdint>
#include <cstring> // for memset

// dumb fucking clang-tidy wants this header instead of <cstdlib>.
// I fucking hate the C++ ecosystem
#include <stdlib.h> // NOLINT

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

#include <chester/bitset.hpp>
#include <chester/file.hpp>
#include <chester/lookup.hpp>
#include <chester/piece_type.hpp>
#include <chester/rank.hpp>
#include <chester/square.hpp>

using chester::bitset;
using chester::file;
using chester::piece_type;
using chester::rank;
using chester::square;

namespace {

namespace bishop {
class table;
}

namespace rook {
class table;
}

constexpr std::size_t TRIALS = 1024UL * 1024UL;
constexpr std::size_t SQUARES = 64;

template <typename Impl, std::size_t N>
class table {
  public:
    std::array<std::uint64_t, SQUARES>     magics;
    std::array<std::size_t,   SQUARES>     cardinalities;
    std::array<bitset,      SQUARES>     masks;
    std::array<bitset,      SQUARES * N> cells;

    constexpr auto lookup(square square, bitset blockers) -> bitset {
#ifdef DEBUG
        if (square.invalid()) {
            throw std::runtime_error("unable to lookup invalid square");
        }
#endif

        const std::size_t i = static_cast<unsigned char>(square.raw);
        const std::size_t j = index(magics[i], blockers & masks[i], cardinalities[i]);
        const std::size_t offset = i * N;

        return cells[offset + j];
    }

  private:
    table()
      : magics(),
        cardinalities(),
        masks(),
        cells()
    {
        for (std::size_t i = 0; i < SQUARES; ++i) {
            const std::size_t offset = i * N;
            const      square square = (class square)i;

            /**
             * Determines if the randomly generated magic number for a trial
             * can uniquely map every blocker configuration to the respective move board.
             *
             * If all configurations map without conflict, `has_collisions` is false;
             * otherwise, it is true.
             */
            bool has_collisions;

            masks[i] = Impl::mask(square);
            cardinalities[i] = masks[i].cardinality();

            for (std::size_t trial = 0; trial < TRIALS; ++trial) {
                (void)trial; // unused

                has_collisions = false;
                magics[i] = (rand64() & rand64() & rand64()); // NOLINT

                for (std::size_t j = offset; j < offset + N; ++j) {
                    cells[j] = bitset::empty();
                }

                for (std::size_t j = 0; j < (1UL << cardinalities[i]); ++j) {
                    const    bitset blockers = masks[i].subset(cardinalities[i], j);
                    const    bitset moves = Impl::moves(square, blockers);
                    const std::size_t k = index(magics[i], blockers, cardinalities[i]);

                    if (cells[offset + k] != bitset::empty()) {
                        has_collisions = true;
                        break;
                    }

                    cells[offset + k] = moves;
                }

                if (!has_collisions) {
                    break;
                }
            }

#ifdef DEBUG
            if (has_collisions) {
                throw std::runtime_error("unable to find a magic number");
            }
#endif // DEBUG
        }
    }

    static constexpr auto index(std::uint64_t magic, bitset blockers, std::size_t cardinality) -> std::size_t {
        return (blockers.raw * magic) >> (SQUARES - cardinality);
    }

    static auto rand64() -> std::uint64_t {
        const std::uint64_t u1 = (std::uint64_t)(random()) & 0xFFFFUL;
        const std::uint64_t u2 = (std::uint64_t)(random()) & 0xFFFFUL;
        const std::uint64_t u3 = (std::uint64_t)(random()) & 0xFFFFUL;
        const std::uint64_t u4 = (std::uint64_t)(random()) & 0xFFFFUL;

        return u1 | (u2 << 16U) | (u3 << 32U) | (u4 << 48U); // NOLINT
    }

    friend ::bishop::table;
    friend   ::rook::table;
};

namespace bishop {

constexpr std::size_t N = 512;

/** lookup table for pseudo-legal moves of a bishop */
class table : public ::table<::bishop::table, N> {
  public:
    table() = default;

    static auto mask(square square) -> bitset {
        const rank rk = square.rank();
        const file fl = square.file();

        auto result = bitset::empty();
        rank r;
        file f;

        for (r = rk + 1, f = fl + 1; r < rank::eight and f < file::h; ++r, ++f) {
            result |= chester::square(f, r);
        }

        for (r = rk + 1, f = fl - 1; r < rank::eight and f > file::a; ++r, --f) {
            result |= chester::square(f, r);
        }

        for (r = rk - 1, f = fl + 1; r > rank::one and f < file::h; --r, ++f) {
            result |= chester::square(f, r);
        }

        for (r = rk - 1, f = fl - 1; r > rank::one and f > file::a; --r, --f) {
            result |= chester::square(f, r);
        }

        return result;
    }

    static constexpr auto moves(square square, bitset blockers) -> bitset {
        const rank rk = square.rank();
        const file fl = square.file();

        auto result = bitset::empty();
        rank r;
        file f;

        for (r = rk + 1, f = fl + 1; r < rank::high and f < file::high; ++r, ++f) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        for (r = rk + 1, f = fl - 1; r < rank::high and f > file::low; ++r, --f) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        for (r = rk - 1, f = fl + 1; r > rank::low and f < file::high; --r, ++f) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        for (r = rk - 1, f = fl - 1; r > rank::low and f > file::low; --r, --f) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        return result;
    }
};

} // namespace bishop

namespace rook {

constexpr std::size_t N = 4096;

/** lookup table for pseudo-legal moves of a rook */
class table : public ::table<::rook::table, N> {
  public:
    table() = default;

    static auto mask(square square) -> bitset {
        const rank rk = square.rank();
        const file fl = square.file();

        auto result = bitset::empty();
        rank r;
        file f;

        for (r = rk + 1, f = fl; r < rank::eight; ++r) {
            result |= chester::square(f, r);
        }

        for (r = rk - 1, f = fl; r > rank::one; --r) {
            result |= chester::square(f, r);
        }

        for (f = fl + 1, r = rk; f < file::h; ++f) {
            result |= chester::square(f, r);
        }

        for (f = fl - 1, r = rk; f > file::a; --f) {
            result |= chester::square(f, r);
        }

        return result;
    }

    static constexpr auto moves(square square, bitset blockers) -> bitset {
        const rank rk = square.rank();
        const file fl = square.file();

        auto result = bitset::empty();
        rank r;
        file f;

        for (r = rk + 1, f = fl; r < rank::high; ++r) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        for (r = rk - 1, f = fl; r > rank::low; --r) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        for (f = fl + 1, r = rk; f < file::high; ++f) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        for (f = fl - 1, r = rk; f > file::low; --f) {
            auto sq = chester::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitset::empty()) {
                break;
            }
        }

        return result;
    }
};

} // namespace rook

} // namespace

template <>
auto chester::lookup::moves<piece_type::bishop>(square square, bitset blockers) -> bitset {
    static ::bishop::table table;

    return table.lookup(square, blockers);
}

template <>
auto chester::lookup::moves<piece_type::rook>(square square, bitset blockers) -> bitset {
    static ::rook::table table;

    return table.lookup(square, blockers);
}

template <>
auto chester::lookup::moves<piece_type::queen>(square square, bitset blockers) -> bitset {
    return lookup::moves<piece_type::bishop>(square, blockers) | lookup::moves<piece_type::rook>(square, blockers);
}
