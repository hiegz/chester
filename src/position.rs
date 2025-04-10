use std::ops::Shl;
use std::ops::ShlAssign;
use std::ops::Shr;
use std::ops::ShrAssign;

#[repr(u8)]
#[rustfmt::skip]
#[allow(unused)]
#[derive(Eq, PartialEq, Clone, Copy, Debug)]
pub enum Square {
    A1 = 7, A2 = 15, A3 = 23, A4 = 31, A5 = 39, A6 = 47, A7 = 55, A8 = 63,
    B1 = 6, B2 = 14, B3 = 22, B4 = 30, B5 = 38, B6 = 46, B7 = 54, B8 = 62,
    C1 = 5, C2 = 13, C3 = 21, C4 = 29, C5 = 37, C6 = 45, C7 = 53, C8 = 61,
    D1 = 4, D2 = 12, D3 = 20, D4 = 28, D5 = 36, D6 = 44, D7 = 52, D8 = 60,
    E1 = 3, E2 = 11, E3 = 19, E4 = 27, E5 = 35, E6 = 43, E7 = 51, E8 = 59,
    F1 = 2, F2 = 10, F3 = 18, F4 = 26, F5 = 34, F6 = 42, F7 = 50, F8 = 58,
    G1 = 1, G2 =  9, G3 = 17, G4 = 25, G5 = 33, G6 = 41, G7 = 49, G8 = 57,
    H1 = 0, H2 =  8, H3 = 16, H4 = 24, H5 = 32, H6 = 40, H7 = 48, H8 = 56,
}

impl Square {
    /// Creates a new square.
    pub fn new(file: File, rank: Rank) -> Square {
        unsafe { std::mem::transmute((rank as u8 - 1) * 8 + (8 - file as u8)) }
    }

    /// Returns the file.
    pub fn file(&self) -> File {
        unsafe { std::mem::transmute(8 - (*self as u8) % 8) }
    }

    /// Returns the rank.
    pub fn rank(&self) -> Rank {
        unsafe { std::mem::transmute((*self as u8) / 8 + 1) }
    }
}

impl From<u8> for Square {
    fn from(value: u8) -> Self {
        unsafe { std::mem::transmute(value) }
    }
}

impl Shl<u8> for Square {
    type Output = Square;

    fn shl(self, rhs: u8) -> Self::Output {
        Square::from(self as u8 + rhs)
    }
}

impl ShlAssign<u8> for Square {
    fn shl_assign(&mut self, rhs: u8) {
        *self = *self << rhs;
    }
}

impl Shr<u8> for Square {
    type Output = Square;

    fn shr(self, rhs: u8) -> Self::Output {
        Square::from(self as u8 - rhs)
    }
}

impl ShrAssign<u8> for Square {
    fn shr_assign(&mut self, rhs: u8) {
        *self = *self >> rhs;
    }
}

#[repr(u8)]
#[allow(unused)]
#[derive(Eq, PartialEq, Clone, Copy, Debug)]
pub enum File {
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    F = 6,
    G = 7,
    H = 8,
}

#[repr(u8)]
#[rustfmt::skip]
#[allow(unused)]
#[derive(Eq, PartialEq, Clone, Copy)]
pub enum Rank {
    One   = 1,
    Two   = 2,
    Three = 3,
    Four  = 4,
    Five  = 5,
    Six   = 6,
    Seven = 7,
    Eight = 8,
}

impl std::fmt::Debug for Rank {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", *self as u8)?;
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn shl() {
        assert_eq!(Square::H2, Square::H1 << 8);
    }

    #[test]
    fn shl_assign() {
        let mut square = Square::C3;
        square <<= 2;
        assert_eq!(Square::A3, square);
    }

    #[test]
    fn shr() {
        assert_eq!(Square::D5, Square::D6 >> 8);
    }

    #[test]
    fn shr_assign() {
        let mut square = Square::H8;
        square >>= 1;
        assert_eq!(Square::A7, square);
    }

    #[test]
    #[rustfmt::skip]
    fn new_position() {
        for (i, &(file, rank, square)) in [
            (File::A, Rank::One,   Square::A1),
            (File::A, Rank::Two,   Square::A2),
            (File::A, Rank::Three, Square::A3),
            (File::A, Rank::Four,  Square::A4),
            (File::A, Rank::Five,  Square::A5),
            (File::A, Rank::Six,   Square::A6),
            (File::A, Rank::Seven, Square::A7),
            (File::A, Rank::Eight, Square::A8),
            (File::B, Rank::One,   Square::B1),
            (File::B, Rank::Two,   Square::B2),
            (File::B, Rank::Three, Square::B3),
            (File::B, Rank::Four,  Square::B4),
            (File::B, Rank::Five,  Square::B5),
            (File::B, Rank::Six,   Square::B6),
            (File::B, Rank::Seven, Square::B7),
            (File::B, Rank::Eight, Square::B8),
            (File::C, Rank::One,   Square::C1),
            (File::C, Rank::Two,   Square::C2),
            (File::C, Rank::Three, Square::C3),
            (File::C, Rank::Four,  Square::C4),
            (File::C, Rank::Five,  Square::C5),
            (File::C, Rank::Six,   Square::C6),
            (File::C, Rank::Seven, Square::C7),
            (File::C, Rank::Eight, Square::C8),
            (File::D, Rank::One,   Square::D1),
            (File::D, Rank::Two,   Square::D2),
            (File::D, Rank::Three, Square::D3),
            (File::D, Rank::Four,  Square::D4),
            (File::D, Rank::Five,  Square::D5),
            (File::D, Rank::Six,   Square::D6),
            (File::D, Rank::Seven, Square::D7),
            (File::D, Rank::Eight, Square::D8),
            (File::F, Rank::One,   Square::F1),
            (File::F, Rank::Two,   Square::F2),
            (File::F, Rank::Three, Square::F3),
            (File::F, Rank::Four,  Square::F4),
            (File::F, Rank::Five,  Square::F5),
            (File::F, Rank::Six,   Square::F6),
            (File::F, Rank::Seven, Square::F7),
            (File::F, Rank::Eight, Square::F8),
            (File::G, Rank::One,   Square::G1),
            (File::G, Rank::Two,   Square::G2),
            (File::G, Rank::Three, Square::G3),
            (File::G, Rank::Four,  Square::G4),
            (File::G, Rank::Five,  Square::G5),
            (File::G, Rank::Six,   Square::G6),
            (File::G, Rank::Seven, Square::G7),
            (File::G, Rank::Eight, Square::G8),
            (File::H, Rank::One,   Square::H1),
            (File::H, Rank::Two,   Square::H2),
            (File::H, Rank::Three, Square::H3),
            (File::H, Rank::Four,  Square::H4),
            (File::H, Rank::Five,  Square::H5),
            (File::H, Rank::Six,   Square::H6),
            (File::H, Rank::Seven, Square::H7),
            (File::H, Rank::Eight, Square::H8),
        ]
        .iter()
        .enumerate()
        {
            let expected = square;
            let actual = Square::new(file, rank);

            assert_eq!(
                expected, actual,
                "Test {} failed : expected {:?}, actual {:?}",
                i, expected, actual
            );
        }
    }

    #[test]
    fn extract_file() {
        for (i, &(square, file)) in [
            (Square::A1, File::A),
            (Square::A2, File::A),
            (Square::A3, File::A),
            (Square::A4, File::A),
            (Square::A5, File::A),
            (Square::A6, File::A),
            (Square::A7, File::A),
            (Square::A8, File::A),
            (Square::B1, File::B),
            (Square::B2, File::B),
            (Square::B3, File::B),
            (Square::B4, File::B),
            (Square::B5, File::B),
            (Square::B6, File::B),
            (Square::B7, File::B),
            (Square::B8, File::B),
            (Square::C1, File::C),
            (Square::C2, File::C),
            (Square::C3, File::C),
            (Square::C4, File::C),
            (Square::C5, File::C),
            (Square::C6, File::C),
            (Square::C7, File::C),
            (Square::C8, File::C),
            (Square::D1, File::D),
            (Square::D2, File::D),
            (Square::D3, File::D),
            (Square::D4, File::D),
            (Square::D5, File::D),
            (Square::D6, File::D),
            (Square::D7, File::D),
            (Square::D8, File::D),
            (Square::E1, File::E),
            (Square::E2, File::E),
            (Square::E3, File::E),
            (Square::E4, File::E),
            (Square::E5, File::E),
            (Square::E6, File::E),
            (Square::E7, File::E),
            (Square::E8, File::E),
            (Square::F1, File::F),
            (Square::F2, File::F),
            (Square::F3, File::F),
            (Square::F4, File::F),
            (Square::F5, File::F),
            (Square::F6, File::F),
            (Square::F7, File::F),
            (Square::F8, File::F),
            (Square::G1, File::G),
            (Square::G2, File::G),
            (Square::G3, File::G),
            (Square::G4, File::G),
            (Square::G5, File::G),
            (Square::G6, File::G),
            (Square::G7, File::G),
            (Square::G8, File::G),
            (Square::H1, File::H),
            (Square::H2, File::H),
            (Square::H3, File::H),
            (Square::H4, File::H),
            (Square::H5, File::H),
            (Square::H6, File::H),
            (Square::H7, File::H),
            (Square::H8, File::H),
        ]
        .iter()
        .enumerate()
        {
            let expected = file;
            let actual = square.file();

            assert_eq!(
                expected, actual,
                "Test {} failed : expected {:?}, actual {:?}",
                i, expected, actual
            );
        }
    }

    #[test]
    fn extract_rank() {
        for (i, &(square, rank)) in [
            (Square::A1, Rank::One),
            (Square::A2, Rank::Two),
            (Square::A3, Rank::Three),
            (Square::A4, Rank::Four),
            (Square::A5, Rank::Five),
            (Square::A6, Rank::Six),
            (Square::A7, Rank::Seven),
            (Square::A8, Rank::Eight),
            (Square::B1, Rank::One),
            (Square::B2, Rank::Two),
            (Square::B3, Rank::Three),
            (Square::B4, Rank::Four),
            (Square::B5, Rank::Five),
            (Square::B6, Rank::Six),
            (Square::B7, Rank::Seven),
            (Square::B8, Rank::Eight),
            (Square::C1, Rank::One),
            (Square::C2, Rank::Two),
            (Square::C3, Rank::Three),
            (Square::C4, Rank::Four),
            (Square::C5, Rank::Five),
            (Square::C6, Rank::Six),
            (Square::C7, Rank::Seven),
            (Square::C8, Rank::Eight),
            (Square::D1, Rank::One),
            (Square::D2, Rank::Two),
            (Square::D3, Rank::Three),
            (Square::D4, Rank::Four),
            (Square::D5, Rank::Five),
            (Square::D6, Rank::Six),
            (Square::D7, Rank::Seven),
            (Square::D8, Rank::Eight),
            (Square::E1, Rank::One),
            (Square::E2, Rank::Two),
            (Square::E3, Rank::Three),
            (Square::E4, Rank::Four),
            (Square::E5, Rank::Five),
            (Square::E6, Rank::Six),
            (Square::E7, Rank::Seven),
            (Square::E8, Rank::Eight),
            (Square::F1, Rank::One),
            (Square::F2, Rank::Two),
            (Square::F3, Rank::Three),
            (Square::F4, Rank::Four),
            (Square::F5, Rank::Five),
            (Square::F6, Rank::Six),
            (Square::F7, Rank::Seven),
            (Square::F8, Rank::Eight),
            (Square::G1, Rank::One),
            (Square::G2, Rank::Two),
            (Square::G3, Rank::Three),
            (Square::G4, Rank::Four),
            (Square::G5, Rank::Five),
            (Square::G6, Rank::Six),
            (Square::G7, Rank::Seven),
            (Square::G8, Rank::Eight),
            (Square::H1, Rank::One),
            (Square::H2, Rank::Two),
            (Square::H3, Rank::Three),
            (Square::H4, Rank::Four),
            (Square::H5, Rank::Five),
            (Square::H6, Rank::Six),
            (Square::H7, Rank::Seven),
            (Square::H8, Rank::Eight),
        ]
        .iter()
        .enumerate()
        {
            let expected = rank;
            let actual = square.rank();

            assert_eq!(
                expected, actual,
                "Test {} failed : expected {:?}, actual {:?}",
                i, expected, actual
            );
        }
    }
}
