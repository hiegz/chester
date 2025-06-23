use std::fmt::Write;

/// A 64-bit set used to efficiently represent piece placement
/// and attack vectors on an 8x8 board.
pub type Bitboard = u64;

/// Wraps the given bitboard to be represented by a debug formatter.
#[derive(Eq, PartialEq)]
pub struct BitboardWrapper(pub Bitboard);

/// Bitboard with all bits set to zero.
pub const EMPTY: Bitboard = 0;

/// Bitboard with all bits set to one.
pub const UNIVERSAL: Bitboard = u64::max_value();

/// Checks if the bitboard is empty.
pub fn is_empty(bitboard: Bitboard) -> bool {
    bitboard == EMPTY
}

/// Checks if the bitboard is universal.
pub fn is_universal(bitboard: Bitboard) -> bool {
    bitboard == UNIVERSAL
}

/// Checks if the bitboard is single populated.
pub fn is_single(bitboard: Bitboard) -> bool {
    bitboard != 0 && (bitboard & (bitboard - 1)) == 0
}

/// Returns the cardinality of a bitboard (i.e., the number of set bits)
pub fn cardinality(mut bitboard: Bitboard) -> usize {
    let mut count = 0;
    while bitboard != 0 {
        count += 1;
        bitboard &= bitboard - 1;
    }
    return count;
}

/// Returns the position of the first least significant set bit.
///
/// In debug mode, this function asserts that the bitboard is not empty.
pub fn bitscan_forward(bitboard: Bitboard) -> u8 {
    debug_assert!(!is_empty(bitboard));

    // Implementation by Kim Walisch (2012)
    //
    // See: https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication

    // TODO: fall back to this approach only if the hardware architecture doesn't provide
    //       BitScan instructions.

    #[rustfmt::skip]
    const INDEX64: [u8; 64] = [
        0,  47,  1, 56, 48, 27,  2, 60,
        57, 49, 41, 37, 28, 16,  3, 61,
        54, 58, 35, 52, 50, 42, 21, 44,
        38, 32, 29, 23, 17, 11,  4, 62,
        46, 55, 26, 59, 40, 36, 15, 53,
        34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30,  9, 24,
        13, 18,  8, 12,  7,  6,  5, 63
    ];
    const DEBRUIJN64: u64 = 0x03f79d71b4cb0a89;

    return INDEX64[((bitboard ^ (bitboard - 1)).wrapping_mul(DEBRUIJN64) as usize) >> 58];
}

/// Returns the position of the first most significant set bit.
///
/// In debug mode, this function asserts that the bitboard is not empty.
pub fn bitscan_reverse(mut bitboard: Bitboard) -> u8 {
    debug_assert!(!is_empty(bitboard));

    // Implementation by Kim Walisch (2012) and Mark Dickinson
    //
    // See: https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication

    // TODO: fall back to this approach only if the hardware architecture doesn't provide
    //       BitScan instructions.

    #[rustfmt::skip]
        const INDEX64: [u8; 64] = [
             0, 47,  1, 56, 48, 27,  2, 60,
            57, 49, 41, 37, 28, 16,  3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11,  4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30,  9, 24,
            13, 18,  8, 12,  7,  6,  5, 63
        ];
    const DEBRUIJN64: u64 = 0x03f79d71b4cb0a89;

    bitboard |= bitboard >> 1;
    bitboard |= bitboard >> 2;
    bitboard |= bitboard >> 4;
    bitboard |= bitboard >> 8;
    bitboard |= bitboard >> 16;
    bitboard |= bitboard >> 32;

    return INDEX64[(bitboard.wrapping_mul(DEBRUIJN64) as usize) >> 58];
}

/// Mirror a bitboard horizontally about the center files.
///
/// File a is mapped to file h and vice versa.
pub fn mirror(mut x: Bitboard) -> Bitboard {
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    // . 1 . 1 . 1 . 1
    const K1: u64 = 0x5555555555555555;

    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    // . . 1 1 . . 1 1
    const K2: u64 = 0x3333333333333333;

    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    // . . . . 1 1 1 1
    const K4: u64 = 0x0f0f0f0f0f0f0f0f;

    x = ((x >> 1) & K1) | ((x & K1) << 1);
    x = ((x >> 2) & K2) | ((x & K2) << 2);
    x = ((x >> 4) & K4) | ((x & K4) << 4);

    return x;
}

impl std::fmt::Debug for BitboardWrapper {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let self_m = mirror(self.0);
        for i in 0..64 {
            f.write_char(if i % 8 == 0 { '\n' } else { ' ' })?;
            let bit = (self_m & (1 << (63 - i))) != 0;
            f.write_char(if bit { '1' } else { '.' })?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    mod bitboard {
        pub use super::super::*;
    }
    use crate::square;

    #[test]
    fn is_empty() {
        assert_eq!(true, bitboard::is_empty(bitboard::EMPTY));
        assert_eq!(false, bitboard::is_empty(bitboard::UNIVERSAL));
    }

    #[test]
    fn is_universal() {
        assert_eq!(true, bitboard::is_universal(bitboard::UNIVERSAL));
        assert_eq!(false, bitboard::is_universal(bitboard::EMPTY));
    }

    #[test]
    fn universal_is_inverted_empty_bitboard() {
        assert_eq!(bitboard::UNIVERSAL, !bitboard::EMPTY);
    }

    #[test]
    fn universal_is_not_single_bitboard() {
        assert!(!bitboard::is_single(bitboard::UNIVERSAL));
    }

    #[test]
    fn universal_cardinality() {
        assert_eq!(64, bitboard::cardinality(bitboard::UNIVERSAL));
    }

    #[test]
    fn universal_bitscan_forward() {
        assert_eq!(square::A1, bitboard::bitscan_forward(bitboard::UNIVERSAL));
    }

    #[test]
    fn universal_bitscan_reverse() {
        assert_eq!(square::H8, bitboard::bitscan_reverse(bitboard::UNIVERSAL));
    }

    #[test]
    fn empty_is_inverted_universal() {
        assert_eq!(bitboard::EMPTY, !bitboard::UNIVERSAL);
    }

    #[test]
    fn empty_is_not_single() {
        assert!(!bitboard::is_single(bitboard::EMPTY));
    }

    #[test]
    fn empty_cardinality() {
        assert_eq!(0, bitboard::cardinality(bitboard::EMPTY));
    }

    #[test]
    fn is_single() {
        for (i, &(squares, is_single)) in [
            (&vec![square::C6], true),
            (&vec![square::B1], true),
            (&vec![square::A8], true),
            (&vec![square::H1], true),
            (&vec![square::B1, square::B2], false),
            (&vec![square::A2, square::D8], false),
            (&vec![square::H1, square::A8, square::D5], false),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = bitboard::EMPTY;
            for &square in squares.iter() {
                bitboard |= 1 << square;
            }
            let bitboard = bitboard;

            assert_eq!(
                is_single,
                bitboard::is_single(bitboard),
                "Test case #{} failed",
                i,
            );
        }
    }

    #[test]
    fn bitboard_cardinality() {
        for (i, &(squares, cardinality)) in [
            (&vec![], 0),
            (&vec![square::C6], 1),
            (&vec![square::B1], 1),
            (&vec![square::A8], 1),
            (&vec![square::H1], 1),
            (&vec![square::B1, square::B2], 2),
            (&vec![square::A2, square::D8], 2),
            (&vec![square::H1, square::A8, square::D5], 3),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = bitboard::EMPTY;
            for &square in squares.iter() {
                bitboard |= 1 << square;
            }
            let bitboard = bitboard;

            assert_eq!(
                cardinality,
                bitboard::cardinality(bitboard),
                "Test case #{} failed",
                i,
            );
        }
    }

    #[test]
    #[rustfmt::skip]
    fn bitscan_forward() {
        for (i, &(squares, lsb)) in [
            (&vec![square::H1], square::H1),
            (&vec![square::A1], square::A1),
            (&vec![square::G2], square::G2),
            (&vec![square::F7], square::F7),
            (&vec![square::A8], square::A8),
            (&vec![square::A5, square::B2], square::B2),
            (&vec![square::C1, square::D1, square::D2], square::C1),
            (&vec![square::F2, square::B1, square::G4], square::B1),
            (&vec![square::E3, square::E4, square::A4], square::E3),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = bitboard::EMPTY;
            for &square in squares.iter() {
                bitboard |= 1 << square;
            }
            let bitboard = bitboard;

            assert_eq!(
                lsb, bitboard::bitscan_forward(bitboard),
                "Test case #{} failed",
                i
            );
        }
    }

    #[test]
    #[rustfmt::skip]
    fn bitscan_reverse() {
        for (i, &(squares, msb)) in [
            (&vec![square::H1], square::H1),
            (&vec![square::A1], square::A1),
            (&vec![square::G2], square::G2),
            (&vec![square::F7], square::F7),
            (&vec![square::A8], square::A8),
            (&vec![square::A5, square::B2], square::A5),
            (&vec![square::C1, square::D1, square::D2], square::D2),
            (&vec![square::F2, square::B1, square::G4], square::G4),
            (&vec![square::E3, square::E4, square::A4], square::E4),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = bitboard::EMPTY;
            for &square in squares.iter() {
                bitboard |= 1 << square;
            }
            let bitboard = bitboard;

            assert_eq!(
                msb, bitboard::bitscan_reverse(bitboard),
                "Test case #{} failed",
                i
            );
        }

    }

    #[test]
    fn mirror() {
        use bitboard::Bitboard;

        // . 1 1 1 1 . . .      . . . 1 1 1 1 .
        // . 1 . . . 1 . .      . . 1 . . . 1 .
        // . 1 . . . 1 . .      . . 1 . . . 1 .
        // . 1 . . 1 . . . -->  . . . 1 . . 1 .
        // . 1 1 1 . . . .      . . . . 1 1 1 .
        // . 1 . 1 . . . .      . . . . 1 . 1 .
        // . 1 . . 1 . . .      . . . 1 . . 1 .
        // . 1 . . . 1 . .      . . 1 . . . 1 .
        const FROM: Bitboard = 0x7844444870504844;
        const TO: Bitboard = 0x1E2222120E0A1222;

        assert_eq!(bitboard::mirror(FROM), TO);
    }
}
