#[repr(u8)]
#[rustfmt::skip]
#[allow(unused)]
#[derive(Eq, PartialEq, Clone, Copy, Debug)]
pub enum Position {
    A1 = 7, A2 = 15, A3 = 23, A4 = 31, A5 = 39, A6 = 47, A7 = 55, A8 = 63,
    B1 = 6, B2 = 14, B3 = 22, B4 = 30, B5 = 38, B6 = 46, B7 = 54, B8 = 62,
    C1 = 5, C2 = 13, C3 = 21, C4 = 29, C5 = 37, C6 = 45, C7 = 53, C8 = 61,
    D1 = 4, D2 = 12, D3 = 20, D4 = 28, D5 = 36, D6 = 44, D7 = 52, D8 = 60,
    E1 = 3, E2 = 11, E3 = 19, E4 = 27, E5 = 35, E6 = 43, E7 = 51, E8 = 59,
    F1 = 2, F2 = 10, F3 = 18, F4 = 26, F5 = 34, F6 = 42, F7 = 50, F8 = 58,
    G1 = 1, G2 =  9, G3 = 17, G4 = 25, G5 = 33, G6 = 41, G7 = 49, G8 = 57,
    H1 = 0, H2 =  8, H3 = 16, H4 = 24, H5 = 32, H6 = 40, H7 = 48, H8 = 56,
}

impl Position {
    /// Creates a new Position.
    pub fn new(file: File, rank: Rank) -> Position {
        unsafe { std::mem::transmute((rank as u8 - 1) * 8 + (8 - file as u8)) }
    }

    /// Extract a file from the position.
    pub fn file(&self) -> File {
        unsafe { std::mem::transmute(8 - (*self as u8) % 8) }
    }

    /// Extract a rank from the position.
    pub fn rank(&self) -> Rank {
        unsafe { std::mem::transmute((*self as u8) / 8 + 1) }
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
    #[rustfmt::skip]
    fn new_position() {
        for (i, &(file, rank, position)) in [
            (File::A, Rank::One,   Position::A1),
            (File::A, Rank::Two,   Position::A2),
            (File::A, Rank::Three, Position::A3),
            (File::A, Rank::Four,  Position::A4),
            (File::A, Rank::Five,  Position::A5),
            (File::A, Rank::Six,   Position::A6),
            (File::A, Rank::Seven, Position::A7),
            (File::A, Rank::Eight, Position::A8),
            (File::B, Rank::One,   Position::B1),
            (File::B, Rank::Two,   Position::B2),
            (File::B, Rank::Three, Position::B3),
            (File::B, Rank::Four,  Position::B4),
            (File::B, Rank::Five,  Position::B5),
            (File::B, Rank::Six,   Position::B6),
            (File::B, Rank::Seven, Position::B7),
            (File::B, Rank::Eight, Position::B8),
            (File::C, Rank::One,   Position::C1),
            (File::C, Rank::Two,   Position::C2),
            (File::C, Rank::Three, Position::C3),
            (File::C, Rank::Four,  Position::C4),
            (File::C, Rank::Five,  Position::C5),
            (File::C, Rank::Six,   Position::C6),
            (File::C, Rank::Seven, Position::C7),
            (File::C, Rank::Eight, Position::C8),
            (File::D, Rank::One,   Position::D1),
            (File::D, Rank::Two,   Position::D2),
            (File::D, Rank::Three, Position::D3),
            (File::D, Rank::Four,  Position::D4),
            (File::D, Rank::Five,  Position::D5),
            (File::D, Rank::Six,   Position::D6),
            (File::D, Rank::Seven, Position::D7),
            (File::D, Rank::Eight, Position::D8),
            (File::F, Rank::One,   Position::F1),
            (File::F, Rank::Two,   Position::F2),
            (File::F, Rank::Three, Position::F3),
            (File::F, Rank::Four,  Position::F4),
            (File::F, Rank::Five,  Position::F5),
            (File::F, Rank::Six,   Position::F6),
            (File::F, Rank::Seven, Position::F7),
            (File::F, Rank::Eight, Position::F8),
            (File::G, Rank::One,   Position::G1),
            (File::G, Rank::Two,   Position::G2),
            (File::G, Rank::Three, Position::G3),
            (File::G, Rank::Four,  Position::G4),
            (File::G, Rank::Five,  Position::G5),
            (File::G, Rank::Six,   Position::G6),
            (File::G, Rank::Seven, Position::G7),
            (File::G, Rank::Eight, Position::G8),
            (File::H, Rank::One,   Position::H1),
            (File::H, Rank::Two,   Position::H2),
            (File::H, Rank::Three, Position::H3),
            (File::H, Rank::Four,  Position::H4),
            (File::H, Rank::Five,  Position::H5),
            (File::H, Rank::Six,   Position::H6),
            (File::H, Rank::Seven, Position::H7),
            (File::H, Rank::Eight, Position::H8),
        ]
        .iter()
        .enumerate()
        {
            let expected = position;
            let actual = Position::new(file, rank);

            assert_eq!(
                expected, actual,
                "Test {} failed : expected {:?}, actual {:?}",
                i, expected, actual
            );
        }
    }

    #[test]
    fn extract_file() {
        for (i, &(position, file)) in [
            (Position::A1, File::A),
            (Position::A2, File::A),
            (Position::A3, File::A),
            (Position::A4, File::A),
            (Position::A5, File::A),
            (Position::A6, File::A),
            (Position::A7, File::A),
            (Position::A8, File::A),
            (Position::B1, File::B),
            (Position::B2, File::B),
            (Position::B3, File::B),
            (Position::B4, File::B),
            (Position::B5, File::B),
            (Position::B6, File::B),
            (Position::B7, File::B),
            (Position::B8, File::B),
            (Position::C1, File::C),
            (Position::C2, File::C),
            (Position::C3, File::C),
            (Position::C4, File::C),
            (Position::C5, File::C),
            (Position::C6, File::C),
            (Position::C7, File::C),
            (Position::C8, File::C),
            (Position::D1, File::D),
            (Position::D2, File::D),
            (Position::D3, File::D),
            (Position::D4, File::D),
            (Position::D5, File::D),
            (Position::D6, File::D),
            (Position::D7, File::D),
            (Position::D8, File::D),
            (Position::E1, File::E),
            (Position::E2, File::E),
            (Position::E3, File::E),
            (Position::E4, File::E),
            (Position::E5, File::E),
            (Position::E6, File::E),
            (Position::E7, File::E),
            (Position::E8, File::E),
            (Position::F1, File::F),
            (Position::F2, File::F),
            (Position::F3, File::F),
            (Position::F4, File::F),
            (Position::F5, File::F),
            (Position::F6, File::F),
            (Position::F7, File::F),
            (Position::F8, File::F),
            (Position::G1, File::G),
            (Position::G2, File::G),
            (Position::G3, File::G),
            (Position::G4, File::G),
            (Position::G5, File::G),
            (Position::G6, File::G),
            (Position::G7, File::G),
            (Position::G8, File::G),
            (Position::H1, File::H),
            (Position::H2, File::H),
            (Position::H3, File::H),
            (Position::H4, File::H),
            (Position::H5, File::H),
            (Position::H6, File::H),
            (Position::H7, File::H),
            (Position::H8, File::H),
        ]
        .iter()
        .enumerate()
        {
            let expected = file;
            let actual = position.file();

            assert_eq!(
                expected, actual,
                "Test {} failed : expected {:?}, actual {:?}",
                i, expected, actual
            );
        }
    }

    #[test]
    fn extract_rank() {
        for (i, &(position, rank)) in [
            (Position::A1, Rank::One),
            (Position::A2, Rank::Two),
            (Position::A3, Rank::Three),
            (Position::A4, Rank::Four),
            (Position::A5, Rank::Five),
            (Position::A6, Rank::Six),
            (Position::A7, Rank::Seven),
            (Position::A8, Rank::Eight),
            (Position::B1, Rank::One),
            (Position::B2, Rank::Two),
            (Position::B3, Rank::Three),
            (Position::B4, Rank::Four),
            (Position::B5, Rank::Five),
            (Position::B6, Rank::Six),
            (Position::B7, Rank::Seven),
            (Position::B8, Rank::Eight),
            (Position::C1, Rank::One),
            (Position::C2, Rank::Two),
            (Position::C3, Rank::Three),
            (Position::C4, Rank::Four),
            (Position::C5, Rank::Five),
            (Position::C6, Rank::Six),
            (Position::C7, Rank::Seven),
            (Position::C8, Rank::Eight),
            (Position::D1, Rank::One),
            (Position::D2, Rank::Two),
            (Position::D3, Rank::Three),
            (Position::D4, Rank::Four),
            (Position::D5, Rank::Five),
            (Position::D6, Rank::Six),
            (Position::D7, Rank::Seven),
            (Position::D8, Rank::Eight),
            (Position::E1, Rank::One),
            (Position::E2, Rank::Two),
            (Position::E3, Rank::Three),
            (Position::E4, Rank::Four),
            (Position::E5, Rank::Five),
            (Position::E6, Rank::Six),
            (Position::E7, Rank::Seven),
            (Position::E8, Rank::Eight),
            (Position::F1, Rank::One),
            (Position::F2, Rank::Two),
            (Position::F3, Rank::Three),
            (Position::F4, Rank::Four),
            (Position::F5, Rank::Five),
            (Position::F6, Rank::Six),
            (Position::F7, Rank::Seven),
            (Position::F8, Rank::Eight),
            (Position::G1, Rank::One),
            (Position::G2, Rank::Two),
            (Position::G3, Rank::Three),
            (Position::G4, Rank::Four),
            (Position::G5, Rank::Five),
            (Position::G6, Rank::Six),
            (Position::G7, Rank::Seven),
            (Position::G8, Rank::Eight),
            (Position::H1, Rank::One),
            (Position::H2, Rank::Two),
            (Position::H3, Rank::Three),
            (Position::H4, Rank::Four),
            (Position::H5, Rank::Five),
            (Position::H6, Rank::Six),
            (Position::H7, Rank::Seven),
            (Position::H8, Rank::Eight),
        ]
        .iter()
        .enumerate()
        {
            let expected = rank;
            let actual = position.rank();

            assert_eq!(
                expected, actual,
                "Test {} failed : expected {:?}, actual {:?}",
                i, expected, actual
            );
        }
    }
}
