use crate::file::File;
use crate::rank::Rank;

pub type Square = u8;

/// Wraps the given square to be represented by a debug formatter.
#[derive(Eq, PartialEq)]
pub struct SquareWrapper(Square);

// A file
pub const A1: Square = 7;
pub const A2: Square = 15;
pub const A3: Square = 23;
pub const A4: Square = 31;
pub const A5: Square = 39;
pub const A6: Square = 47;
pub const A7: Square = 55;
pub const A8: Square = 63;

// B file
pub const B1: Square = 6;
pub const B2: Square = 14;
pub const B3: Square = 22;
pub const B4: Square = 30;
pub const B5: Square = 38;
pub const B6: Square = 46;
pub const B7: Square = 54;
pub const B8: Square = 62;

// C file
pub const C1: Square = 5;
pub const C2: Square = 13;
pub const C3: Square = 21;
pub const C4: Square = 29;
pub const C5: Square = 37;
pub const C6: Square = 45;
pub const C7: Square = 53;
pub const C8: Square = 61;

// D file
pub const D1: Square = 4;
pub const D2: Square = 12;
pub const D3: Square = 20;
pub const D4: Square = 28;
pub const D5: Square = 36;
pub const D6: Square = 44;
pub const D7: Square = 52;
pub const D8: Square = 60;

// E file
pub const E1: Square = 3;
pub const E2: Square = 11;
pub const E3: Square = 19;
pub const E4: Square = 27;
pub const E5: Square = 35;
pub const E6: Square = 43;
pub const E7: Square = 51;
pub const E8: Square = 59;

// F file
pub const F1: Square = 2;
pub const F2: Square = 10;
pub const F3: Square = 18;
pub const F4: Square = 26;
pub const F5: Square = 34;
pub const F6: Square = 42;
pub const F7: Square = 50;
pub const F8: Square = 58;

// G file
pub const G1: Square = 1;
pub const G2: Square = 9;
pub const G3: Square = 17;
pub const G4: Square = 25;
pub const G5: Square = 33;
pub const G6: Square = 41;
pub const G7: Square = 49;
pub const G8: Square = 57;

// H file
pub const H1: Square = 0;
pub const H2: Square = 8;
pub const H3: Square = 16;
pub const H4: Square = 24;
pub const H5: Square = 32;
pub const H6: Square = 40;
pub const H7: Square = 48;
pub const H8: Square = 56;

/// Creates a new square from the provided file and rank.
pub fn compose(file: File, rank: Rank) -> Square {
    std::debug_assert!(file < 8 && rank >= 1 && rank <= 8);
    (rank - 1) * 8 + (7 - file)
}

/// Returns the square file.
pub fn file(square: Square) -> File {
    8 - square % 8 - 1
}

/// Returns the square rank.
pub fn rank(square: Square) -> Rank {
    square / 8 + 1
}

impl std::fmt::Debug for SquareWrapper {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}{}", file(self.0), rank(self.0))
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
            (file::A, 1, square::A1),
            (file::A, 2, square::A2),
            (file::A, 3, square::A3),
            (file::A, 4, square::A4),
            (file::A, 5, square::A5),
            (file::A, 6, square::A6),
            (file::A, 7, square::A7),
            (file::A, 8, square::A8),
            (file::B, 1, square::B1),
            (file::B, 2, square::B2),
            (file::B, 3, square::B3),
            (file::B, 4, square::B4),
            (file::B, 5, square::B5),
            (file::B, 6, square::B6),
            (file::B, 7, square::B7),
            (file::B, 8, square::B8),
            (file::C, 1, square::C1),
            (file::C, 2, square::C2),
            (file::C, 3, square::C3),
            (file::C, 4, square::C4),
            (file::C, 5, square::C5),
            (file::C, 6, square::C6),
            (file::C, 7, square::C7),
            (file::C, 8, square::C8),
            (file::D, 1, square::D1),
            (file::D, 2, square::D2),
            (file::D, 3, square::D3),
            (file::D, 4, square::D4),
            (file::D, 5, square::D5),
            (file::D, 6, square::D6),
            (file::D, 7, square::D7),
            (file::D, 8, square::D8),
            (file::F, 1, square::F1),
            (file::F, 2, square::F2),
            (file::F, 3, square::F3),
            (file::F, 4, square::F4),
            (file::F, 5, square::F5),
            (file::F, 6, square::F6),
            (file::F, 7, square::F7),
            (file::F, 8, square::F8),
            (file::G, 1, square::G1),
            (file::G, 2, square::G2),
            (file::G, 3, square::G3),
            (file::G, 4, square::G4),
            (file::G, 5, square::G5),
            (file::G, 6, square::G6),
            (file::G, 7, square::G7),
            (file::G, 8, square::G8),
            (file::H, 1, square::H1),
            (file::H, 2, square::H2),
            (file::H, 3, square::H3),
            (file::H, 4, square::H4),
            (file::H, 5, square::H5),
            (file::H, 6, square::H6),
            (file::H, 7, square::H7),
            (file::H, 8, square::H8),
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
            (square::A1, 1),
            (square::A2, 2),
            (square::A3, 3),
            (square::A4, 4),
            (square::A5, 5),
            (square::A6, 6),
            (square::A7, 7),
            (square::A8, 8),
            (square::B1, 1),
            (square::B2, 2),
            (square::B3, 3),
            (square::B4, 4),
            (square::B5, 5),
            (square::B6, 6),
            (square::B7, 7),
            (square::B8, 8),
            (square::C1, 1),
            (square::C2, 2),
            (square::C3, 3),
            (square::C4, 4),
            (square::C5, 5),
            (square::C6, 6),
            (square::C7, 7),
            (square::C8, 8),
            (square::D1, 1),
            (square::D2, 2),
            (square::D3, 3),
            (square::D4, 4),
            (square::D5, 5),
            (square::D6, 6),
            (square::D7, 7),
            (square::D8, 8),
            (square::E1, 1),
            (square::E2, 2),
            (square::E3, 3),
            (square::E4, 4),
            (square::E5, 5),
            (square::E6, 6),
            (square::E7, 7),
            (square::E8, 8),
            (square::F1, 1),
            (square::F2, 2),
            (square::F3, 3),
            (square::F4, 4),
            (square::F5, 5),
            (square::F6, 6),
            (square::F7, 7),
            (square::F8, 8),
            (square::G1, 1),
            (square::G2, 2),
            (square::G3, 3),
            (square::G4, 4),
            (square::G5, 5),
            (square::G6, 6),
            (square::G7, 7),
            (square::G8, 8),
            (square::H1, 1),
            (square::H2, 2),
            (square::H3, 3),
            (square::H4, 4),
            (square::H5, 5),
            (square::H6, 6),
            (square::H7, 7),
            (square::H8, 8),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(rank, square::rank(square), "Test case #{} failed", i);
        }
    }
}
