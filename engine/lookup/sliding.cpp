// NOLINTBEGIN
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

#include <chester/engine/bitboard.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/lookup.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/square.hpp>

using chester::engine::bitboard;
using chester::engine::file;
using chester::engine::piece;
using chester::engine::rank;
using chester::engine::square;

namespace {

namespace bishop {
class table;
}

constexpr std::size_t TRIALS = 1024UL * 1024UL;
constexpr std::size_t SQUARES = 64;

template <typename Impl, std::size_t N>
class table {
  public:
    std::array<std::uint64_t, SQUARES>     magics;
    std::array<std::size_t,   SQUARES>     cardinalities;
    std::array<bitboard,      SQUARES>     masks;
    std::array<bitboard,      SQUARES * N> cells;

    constexpr auto lookup(square square, bitboard blockers) -> bitboard {
        const std::size_t i = square.value;
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
            const      square square = (class square)(enum square::value)i;

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
                    cells[j] = bitboard::empty();
                }

                for (std::size_t j = 0; j < (1UL << cardinalities[i]); ++j) {
                    const    bitboard blockers = bitboard::subset(masks[i], cardinalities[i], j);
                    const    bitboard moves = Impl::moves(square, blockers);
                    const std::size_t k = index(magics[i], blockers, cardinalities[i]);

                    if (cells[offset + k] != bitboard::empty()) {
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

    static constexpr auto index(std::uint64_t magic, bitboard blockers, std::size_t cardinality) -> std::size_t {
        return (blockers.value * magic) >> (SQUARES - cardinality);
    }

    static auto rand64() -> std::uint64_t {
        const std::uint64_t u1 = (std::uint64_t)(random()) & 0xFFFFUL;
        const std::uint64_t u2 = (std::uint64_t)(random()) & 0xFFFFUL;
        const std::uint64_t u3 = (std::uint64_t)(random()) & 0xFFFFUL;
        const std::uint64_t u4 = (std::uint64_t)(random()) & 0xFFFFUL;

        return u1 | (u2 << 16U) | (u3 << 32U) | (u4 << 48U); // NOLINT
    }

    friend ::bishop::table;
};

namespace bishop {

constexpr std::size_t N = 512;

/** lookup table for pseudo-legal moves of a bishop */
class table : public ::table<::bishop::table, N> {
  public:
    table() = default;

    static auto mask(square square) -> bitboard {
        const rank rk = square.rank();
        const file fl = square.file();

        auto result = bitboard::empty();
        rank r;
        file f;

        for (r = rk + 1, f = fl + 1; r < rank::eight and f < file::h; ++r, ++f) {
            result |= chester::engine::square(f, r);
        }

        for (r = rk + 1, f = fl - 1; r < rank::eight and f > file::a; ++r, --f) {
            result |= chester::engine::square(f, r);
        }

        for (r = rk - 1, f = fl + 1; r > rank::one and f < file::h; --r, ++f) {
            result |= chester::engine::square(f, r);
        }

        for (r = rk - 1, f = fl - 1; r > rank::one and f > file::a; --r, --f) {
            result |= chester::engine::square(f, r);
        }

        return result;
    }

    static constexpr auto moves(square square, bitboard blockers) -> bitboard {
        const rank rk = square.rank();
        const file fl = square.file();

        auto result = bitboard::empty();
        rank r;
        file f;

        for (r = rk + 1, f = fl + 1; r < rank::high and f < file::high; ++r, ++f) {
            auto sq = chester::engine::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitboard::empty()) {
                break;
            }
        }

        for (r = rk + 1, f = fl - 1; r < rank::high and f > file::low; ++r, --f) {
            auto sq = chester::engine::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitboard::empty()) {
                break;
            }
        }

        for (r = rk - 1, f = fl + 1; r > rank::low and f < file::high; --r, ++f) {
            auto sq = chester::engine::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitboard::empty()) {
                break;
            }
        }

        for (r = rk - 1, f = fl - 1; r > rank::low and f > file::low; --r, --f) {
            auto sq = chester::engine::square(f, r);
            result |= sq;
            if ((blockers & sq) != bitboard::empty()) {
                break;
            }
        }

        return result;
    }
};

} // namespace bishop
} // namespace

template <>
auto chester::engine::lookup<piece::bishop>(square square, bitboard blockers) -> bitboard {
    static ::bishop::table table;

    return table.lookup(square, blockers);
}
