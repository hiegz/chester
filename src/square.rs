use crate::file::File;
use crate::file::FileWrapper;
use crate::rank::Rank;
use crate::rank::RankWrapper;

pub type Square = u8;

/// Wraps the given square to be represented by a debug formatter.
#[derive(Eq, PartialEq)]
pub struct SquareWrapper(pub Square);

// A file
pub const A1: Square = 0;
pub const A2: Square = 8;
pub const A3: Square = 16;
pub const A4: Square = 24;
pub const A5: Square = 32;
pub const A6: Square = 40;
pub const A7: Square = 48;
pub const A8: Square = 56;

// B file
pub const B1: Square = 1;
pub const B2: Square = 9;
pub const B3: Square = 17;
pub const B4: Square = 25;
pub const B5: Square = 33;
pub const B6: Square = 41;
pub const B7: Square = 49;
pub const B8: Square = 57;

// C file
pub const C1: Square = 2;
pub const C2: Square = 10;
pub const C3: Square = 18;
pub const C4: Square = 26;
pub const C5: Square = 34;
pub const C6: Square = 42;
pub const C7: Square = 50;
pub const C8: Square = 58;

// D file
pub const D1: Square = 3;
pub const D2: Square = 11;
pub const D3: Square = 19;
pub const D4: Square = 27;
pub const D5: Square = 35;
pub const D6: Square = 43;
pub const D7: Square = 51;
pub const D8: Square = 59;

// E file
pub const E1: Square = 4;
pub const E2: Square = 12;
pub const E3: Square = 20;
pub const E4: Square = 28;
pub const E5: Square = 36;
pub const E6: Square = 44;
pub const E7: Square = 52;
pub const E8: Square = 60;

// F file
pub const F1: Square = 5;
pub const F2: Square = 13;
pub const F3: Square = 21;
pub const F4: Square = 29;
pub const F5: Square = 37;
pub const F6: Square = 45;
pub const F7: Square = 53;
pub const F8: Square = 61;

// G file
pub const G1: Square = 6;
pub const G2: Square = 14;
pub const G3: Square = 22;
pub const G4: Square = 30;
pub const G5: Square = 38;
pub const G6: Square = 46;
pub const G7: Square = 54;
pub const G8: Square = 62;

// H file
pub const H1: Square = 7;
pub const H2: Square = 15;
pub const H3: Square = 23;
pub const H4: Square = 31;
pub const H5: Square = 39;
pub const H6: Square = 47;
pub const H7: Square = 55;
pub const H8: Square = 63;

/// Creates a new square from the provided file and rank.
pub fn compose(file: File, rank: Rank) -> Square {
    std::debug_assert!(file <= 7 && rank <= 7);
    rank * 8 + file
}

/// Returns the square file.
pub fn file(square: Square) -> File {
    square % 8
}

/// Returns the square rank.
pub fn rank(square: Square) -> Rank {
    square / 8
}

impl std::fmt::Debug for SquareWrapper {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{:?}{:?}",
            FileWrapper(file(self.0)),
            RankWrapper(rank(self.0))
        )
    }
}

#[cfg(test)]
mod test {
    mod square {
        pub use super::super::*;
    }
    use crate::file;

    #[test]
    fn compose() {
        for (i, &(file, rank, square)) in [
            (file::A, 0, square::A1),
            (file::A, 1, square::A2),
            (file::A, 2, square::A3),
            (file::A, 3, square::A4),
            (file::A, 4, square::A5),
            (file::A, 5, square::A6),
            (file::A, 6, square::A7),
            (file::A, 7, square::A8),
            (file::B, 0, square::B1),
            (file::B, 1, square::B2),
            (file::B, 2, square::B3),
            (file::B, 3, square::B4),
            (file::B, 4, square::B5),
            (file::B, 5, square::B6),
            (file::B, 6, square::B7),
            (file::B, 7, square::B8),
            (file::C, 0, square::C1),
            (file::C, 1, square::C2),
            (file::C, 2, square::C3),
            (file::C, 3, square::C4),
            (file::C, 4, square::C5),
            (file::C, 5, square::C6),
            (file::C, 6, square::C7),
            (file::C, 7, square::C8),
            (file::D, 0, square::D1),
            (file::D, 1, square::D2),
            (file::D, 2, square::D3),
            (file::D, 3, square::D4),
            (file::D, 4, square::D5),
            (file::D, 5, square::D6),
            (file::D, 6, square::D7),
            (file::D, 7, square::D8),
            (file::F, 0, square::F1),
            (file::F, 1, square::F2),
            (file::F, 2, square::F3),
            (file::F, 3, square::F4),
            (file::F, 4, square::F5),
            (file::F, 5, square::F6),
            (file::F, 6, square::F7),
            (file::F, 7, square::F8),
            (file::G, 0, square::G1),
            (file::G, 1, square::G2),
            (file::G, 2, square::G3),
            (file::G, 3, square::G4),
            (file::G, 4, square::G5),
            (file::G, 5, square::G6),
            (file::G, 6, square::G7),
            (file::G, 7, square::G8),
            (file::H, 0, square::H1),
            (file::H, 1, square::H2),
            (file::H, 2, square::H3),
            (file::H, 3, square::H4),
            (file::H, 4, square::H5),
            (file::H, 5, square::H6),
            (file::H, 6, square::H7),
            (file::H, 7, square::H8),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(
                square,
                square::compose(file, rank),
                "Test case #{} failed",
                i
            );
        }
    }

    #[test]
    fn file() {
        for (i, &(square, file)) in [
            (square::A1, file::A),
            (square::A2, file::A),
            (square::A3, file::A),
            (square::A4, file::A),
            (square::A5, file::A),
            (square::A6, file::A),
            (square::A7, file::A),
            (square::A8, file::A),
            (square::B1, file::B),
            (square::B2, file::B),
            (square::B3, file::B),
            (square::B4, file::B),
            (square::B5, file::B),
            (square::B6, file::B),
            (square::B7, file::B),
            (square::B8, file::B),
            (square::C1, file::C),
            (square::C2, file::C),
            (square::C3, file::C),
            (square::C4, file::C),
            (square::C5, file::C),
            (square::C6, file::C),
            (square::C7, file::C),
            (square::C8, file::C),
            (square::D1, file::D),
            (square::D2, file::D),
            (square::D3, file::D),
            (square::D4, file::D),
            (square::D5, file::D),
            (square::D6, file::D),
            (square::D7, file::D),
            (square::D8, file::D),
            (square::E1, file::E),
            (square::E2, file::E),
            (square::E3, file::E),
            (square::E4, file::E),
            (square::E5, file::E),
            (square::E6, file::E),
            (square::E7, file::E),
            (square::E8, file::E),
            (square::F1, file::F),
            (square::F2, file::F),
            (square::F3, file::F),
            (square::F4, file::F),
            (square::F5, file::F),
            (square::F6, file::F),
            (square::F7, file::F),
            (square::F8, file::F),
            (square::G1, file::G),
            (square::G2, file::G),
            (square::G3, file::G),
            (square::G4, file::G),
            (square::G5, file::G),
            (square::G6, file::G),
            (square::G7, file::G),
            (square::G8, file::G),
            (square::H1, file::H),
            (square::H2, file::H),
            (square::H3, file::H),
            (square::H4, file::H),
            (square::H5, file::H),
            (square::H6, file::H),
            (square::H7, file::H),
            (square::H8, file::H),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(file, square::file(square), "Test case #{} failed", i);
        }
    }

    #[test]
    fn rank() {
        for (i, &(square, rank)) in [
            (square::A1, 0),
            (square::A2, 1),
            (square::A3, 2),
            (square::A4, 3),
            (square::A5, 4),
            (square::A6, 5),
            (square::A7, 6),
            (square::A8, 7),
            (square::B1, 0),
            (square::B2, 1),
            (square::B3, 2),
            (square::B4, 3),
            (square::B5, 4),
            (square::B6, 5),
            (square::B7, 6),
            (square::B8, 7),
            (square::C1, 0),
            (square::C2, 1),
            (square::C3, 2),
            (square::C4, 3),
            (square::C5, 4),
            (square::C6, 5),
            (square::C7, 6),
            (square::C8, 7),
            (square::D1, 0),
            (square::D2, 1),
            (square::D3, 2),
            (square::D4, 3),
            (square::D5, 4),
            (square::D6, 5),
            (square::D7, 6),
            (square::D8, 7),
            (square::E1, 0),
            (square::E2, 1),
            (square::E3, 2),
            (square::E4, 3),
            (square::E5, 4),
            (square::E6, 5),
            (square::E7, 6),
            (square::E8, 7),
            (square::F1, 0),
            (square::F2, 1),
            (square::F3, 2),
            (square::F4, 3),
            (square::F5, 4),
            (square::F6, 5),
            (square::F7, 6),
            (square::F8, 7),
            (square::G1, 0),
            (square::G2, 1),
            (square::G3, 2),
            (square::G4, 3),
            (square::G5, 4),
            (square::G6, 5),
            (square::G7, 6),
            (square::G8, 7),
            (square::H1, 0),
            (square::H2, 1),
            (square::H3, 2),
            (square::H4, 3),
            (square::H5, 4),
            (square::H6, 5),
            (square::H7, 6),
            (square::H8, 7),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(rank, square::rank(square), "Test case #{} failed", i);
        }
    }
}
