use std::fmt::Write;

use std::ops::BitAnd;
use std::ops::BitAndAssign;
use std::ops::BitOr;
use std::ops::BitOrAssign;
use std::ops::BitXor;
use std::ops::BitXorAssign;
use std::ops::Not;
use std::ops::Shl;
use std::ops::ShlAssign;
use std::ops::Shr;
use std::ops::ShrAssign;

use crate::position::Position;

/// A 64-bit set used to efficiently represent piece placement
/// and attack vectors on an 8x8 board.
#[derive(Eq, PartialEq, Clone, Copy)]
pub struct Bitboard(u64);

impl Bitboard {
    /// Returns a new bitboard with all bits set to zero.
    pub fn empty() -> Self {
        Bitboard::from(0)
    }

    /// Checks if the bitboard is empty.
    pub fn is_empty(&self) -> bool {
        *self == Bitboard::empty()
    }

    /// Returns a new bitboard with all bits set to one.
    pub fn universal() -> Bitboard {
        Bitboard::from(u64::max_value())
    }

    /// Checks if the bitboard is universal.
    pub fn is_universal(&self) -> bool {
        *self == Bitboard::universal()
    }

    /// Checks if the bitboard is single populated.
    pub fn is_single(&self) -> bool {
        self.0 != 0 && (self.0 & (self.0 - 1)) == 0
    }
}

impl Bitboard {
    /// Sets the bit at the given position.
    pub fn set(&mut self, position: Position) {
        self.0 |= 1 << position as u32;
    }

    /// Resets the bit at the given position.
    pub fn reset(&mut self, position: Position) {
        self.0 &= !(1 << position as u32);
    }

    /// Checks whether the bit at the given position is set.
    pub fn is_set(&self, position: Position) -> bool {
        self.0 & (1 << position as u32) != 0
    }

    /// Returns the cardinality of a bitboard (i.e., the number of set bits)
    pub fn cardinality(&self) -> usize {
        let mut x = self.clone();
        let mut count = 0;
        while x.0 != 0 {
            count += 1;
            x.0 &= x.0 - 1;
        }
        return count;
    }
}

impl Bitboard {
    /// Returns the position of the first least significant set bit.
    ///
    /// In debug mode, this function asserts that the bitboard is not empty.
    pub fn bitscan_forward(&self) -> Position {
        debug_assert!(!self.is_empty());

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

        let index = INDEX64[((self.0 ^ (self.0 - 1)).wrapping_mul(DEBRUIJN64) as usize) >> 58];
        unsafe { std::mem::transmute(index) }
    }

    /// Returns the position of the first most significant set bit.
    ///
    /// In debug mode, this function asserts that the bitboard is not empty.
    pub fn bitscan_reverse(&self) -> Position {
        debug_assert!(!self.is_empty());

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

        let mut x = self.0;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        x |= x >> 32;

        let index = INDEX64[(x.wrapping_mul(DEBRUIJN64) as usize) >> 58];
        unsafe { std::mem::transmute(index) }
    }
}

impl Default for Bitboard {
    fn default() -> Self {
        return Bitboard(0);
    }
}

impl From<u64> for Bitboard {
    fn from(value: u64) -> Self {
        return Bitboard(value);
    }
}

impl From<Bitboard> for u64 {
    fn from(value: Bitboard) -> Self {
        return value.0;
    }
}

impl From<Position> for Bitboard {
    fn from(value: Position) -> Self {
        Bitboard::empty() | (1u64 << (value as u8))
    }
}

impl BitAnd for Bitboard {
    type Output = Bitboard;

    fn bitand(self, rhs: Self) -> Self::Output {
        Bitboard::from(self.0.bitand(rhs.0))
    }
}

impl BitAnd<u64> for Bitboard {
    type Output = Bitboard;

    fn bitand(self, rhs: u64) -> Self::Output {
        Bitboard::from(self.0.bitand(rhs))
    }
}

impl BitAndAssign for Bitboard {
    fn bitand_assign(&mut self, rhs: Self) {
        self.0.bitand_assign(rhs.0);
    }
}

impl BitAndAssign<u64> for Bitboard {
    fn bitand_assign(&mut self, rhs: u64) {
        self.0.bitand_assign(rhs);
    }
}

impl BitOr for Bitboard {
    type Output = Bitboard;

    fn bitor(self, rhs: Self) -> Self::Output {
        Bitboard::from(self.0.bitor(rhs.0))
    }
}

impl BitOr<u64> for Bitboard {
    type Output = Bitboard;

    fn bitor(self, rhs: u64) -> Self::Output {
        Bitboard::from(self.0.bitor(rhs))
    }
}

impl BitOrAssign for Bitboard {
    fn bitor_assign(&mut self, rhs: Self) {
        self.0.bitor_assign(rhs.0);
    }
}

impl BitOrAssign<u64> for Bitboard {
    fn bitor_assign(&mut self, rhs: u64) {
        self.0.bitor_assign(rhs);
    }
}

impl BitXor for Bitboard {
    type Output = Bitboard;

    fn bitxor(self, rhs: Self) -> Self::Output {
        Bitboard::from(self.0.bitxor(rhs.0))
    }
}

impl BitXor<u64> for Bitboard {
    type Output = Bitboard;

    fn bitxor(self, rhs: u64) -> Self::Output {
        Bitboard::from(self.0.bitxor(rhs))
    }
}

impl BitXorAssign for Bitboard {
    fn bitxor_assign(&mut self, rhs: Self) {
        self.0.bitxor_assign(rhs.0);
    }
}

impl BitXorAssign<u64> for Bitboard {
    fn bitxor_assign(&mut self, rhs: u64) {
        self.0.bitxor_assign(rhs);
    }
}

impl Shl<u32> for Bitboard {
    type Output = Bitboard;

    fn shl(self, rhs: u32) -> Self::Output {
        Bitboard::from(self.0.shl(rhs))
    }
}

impl ShlAssign<u32> for Bitboard {
    fn shl_assign(&mut self, rhs: u32) {
        self.0.shl_assign(rhs);
    }
}

impl Shr<u32> for Bitboard {
    type Output = Bitboard;

    fn shr(self, rhs: u32) -> Self::Output {
        Bitboard::from(self.0.shr(rhs))
    }
}

impl ShrAssign<u32> for Bitboard {
    fn shr_assign(&mut self, rhs: u32) {
        self.0.shr_assign(rhs);
    }
}

impl Not for Bitboard {
    type Output = Bitboard;

    fn not(self) -> Self::Output {
        Bitboard::from(self.0.not())
    }
}

impl std::fmt::Debug for Bitboard {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for i in 0..64 {
            f.write_char(if i % 8 == 0 { '\n' } else { ' ' })?;
            let bit = (self.0 & (1 << (63 - i))) != 0;
            f.write_char(if bit { '1' } else { '.' })?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    macro_rules! chessboard {
        ($line0:tt $line1:tt $line2:tt $line3:tt $line4:tt $line5:tt $line6:tt $line7:tt) => {
            ($line0 << 56)
                | ($line1 << 48)
                | ($line2 << 40)
                | ($line3 << 32)
                | ($line4 << 24)
                | ($line5 << 16)
                | ($line6 << 8)
                | ($line7 << 0)
        };
    }

    #[test]
    fn empty_bitboard() {
        assert_eq!(0, u64::from(Bitboard::empty()));
        assert_eq!(true, Bitboard::empty().is_empty());
        assert_eq!(false, Bitboard::empty().is_universal());
    }

    #[test]
    fn is_empty_bitboard() {
        assert_eq!(true, Bitboard::empty().is_empty());
        assert_eq!(false, Bitboard::universal().is_empty());
    }

    #[test]
    fn universal_bitboard() {
        assert_eq!(0xffffffffffffffff, u64::from(Bitboard::universal()));
        assert_eq!(true, Bitboard::universal().is_universal());
        assert_eq!(false, Bitboard::universal().is_empty());
    }

    #[test]
    fn is_universal_bitboard() {
        assert_eq!(true, Bitboard::universal().is_universal());
        assert_eq!(false, Bitboard::empty().is_universal());
    }

    #[test]
    fn universal_is_inverted_empty() {
        assert_eq!(Bitboard::universal(), !Bitboard::empty());
    }

    #[test]
    fn universal_is_not_single() {
        assert!(!(Bitboard::universal().is_single()));
    }

    #[test]
    fn universal_cardinality() {
        assert_eq!(64, Bitboard::universal().cardinality());
    }

    #[test]
    fn universal_bitscan_forward() {
        assert_eq!(Position::H1, Bitboard::universal().bitscan_forward());
    }

    #[test]
    fn universal_bitscan_reverse() {
        assert_eq!(Position::A8, Bitboard::universal().bitscan_reverse());
    }

    #[test]
    fn empty_is_inverted_universal() {
        assert_eq!(Bitboard::empty(), !Bitboard::universal());
    }

    #[test]
    fn empty_is_not_single() {
        assert!(!(Bitboard::empty().is_single()));
    }

    #[test]
    fn empty_cardinality() {
        assert_eq!(0, Bitboard::empty().cardinality());
    }

    #[test]
    fn is_single() {
        for (i, &(positions, is_single)) in [
            (&vec![Position::C6], true),
            (&vec![Position::B1], true),
            (&vec![Position::A8], true),
            (&vec![Position::H1], true),
            (&vec![Position::B1, Position::B2], false),
            (&vec![Position::A2, Position::D8], false),
            (&vec![Position::H1, Position::A8, Position::D5], false),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = Bitboard::empty();
            for &position in positions.iter() {
                bitboard.set(position);
            }
            let bitboard = bitboard;

            assert_eq!(
                is_single,
                bitboard.is_single(),
                "Test {} failed. Expected {:?}, found {:?}",
                i,
                is_single,
                bitboard.is_single()
            );
        }
    }

    #[test]
    fn bitboard_cardinality() {
        for (i, &(positions, cardinality)) in [
            (&vec![], 0),
            (&vec![Position::C6], 1),
            (&vec![Position::B1], 1),
            (&vec![Position::A8], 1),
            (&vec![Position::H1], 1),
            (&vec![Position::B1, Position::B2], 2),
            (&vec![Position::A2, Position::D8], 2),
            (&vec![Position::H1, Position::A8, Position::D5], 3),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = Bitboard::empty();
            for &position in positions.iter() {
                bitboard.set(position);
            }
            let bitboard = bitboard;

            assert_eq!(
                cardinality,
                bitboard.cardinality(),
                "Test {} failed. Expected {:?}, found {:?}",
                i,
                cardinality,
                bitboard.cardinality(),
            );
        }
    }

    #[test]
    fn bitboard_set() {
        let expected = Bitboard::from(chessboard!(
                0b_00000000
                0b_00000000
                0b_00000000
                0b_00000001
                0b_00000000
                0b_10000000
                0b_00000000
                0b_00000001));

        let mut bitboard = Bitboard::empty();
        bitboard.set(Position::H1);
        bitboard.set(Position::H5);
        bitboard.set(Position::A3);

        assert_eq!(expected, bitboard);
    }

    #[test]
    fn bitboard_reset() {
        let expected = Bitboard::from(chessboard!(
                0b_00010000
                0b_00000000
                0b_00000100
                0b_00000000
                0b_00000000
                0b_00100000
                0b_00000010
                0b_00000000));

        let mut bitboard = Bitboard::empty();

        bitboard.set(Position::H1);
        bitboard.set(Position::H5);
        bitboard.set(Position::A3);

        bitboard.set(Position::G2);
        bitboard.set(Position::C3);
        bitboard.set(Position::F6);
        bitboard.set(Position::D8);

        bitboard.reset(Position::H1);
        bitboard.reset(Position::H5);
        bitboard.reset(Position::A3);

        assert_eq!(expected, bitboard);
    }

    #[test]
    fn bitboard_is_set() {
        let bitboard = Bitboard::from(chessboard!(
                0b_00010000
                0b_00000000
                0b_00000100
                0b_00000000
                0b_00000000
                0b_00100000
                0b_00000010
                0b_00000000));

        assert!(bitboard.is_set(Position::G2));
        assert!(bitboard.is_set(Position::C3));
        assert!(bitboard.is_set(Position::F6));
        assert!(bitboard.is_set(Position::D8));
        assert!(!bitboard.is_set(Position::A5));
        assert!(!bitboard.is_set(Position::A1));
        assert!(!bitboard.is_set(Position::B4));
    }

    #[test]
    #[rustfmt::skip]
    fn bitscan_forward() {
        for (i, &(positions, lsb)) in [
            (&vec![Position::H1], Position::H1),
            (&vec![Position::A1], Position::A1),
            (&vec![Position::G2], Position::G2),
            (&vec![Position::F7], Position::F7),
            (&vec![Position::A8], Position::A8),
            (&vec![Position::A5, Position::B2], Position::B2),
            (&vec![Position::C1, Position::D1, Position::D2], Position::D1),
            (&vec![Position::F2, Position::B1, Position::G4], Position::B1),
            (&vec![Position::E3, Position::E4, Position::A4], Position::E3),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = Bitboard::empty();
            for &position in positions.iter() {
                bitboard.set(position);
            }
            let bitboard = bitboard;

            let expected = lsb;
            let actual = bitboard.bitscan_forward();

            assert_eq!(
                expected, actual,
                "Test {} failed. Expected {:?}, found {:?}",
                i, expected, actual
            );
        }
    }

    #[test]
    #[rustfmt::skip]
    fn bitscan_reverse() {
        for (i, &(positions, msb)) in [
            (&vec![Position::H1], Position::H1),
            (&vec![Position::A1], Position::A1),
            (&vec![Position::G2], Position::G2),
            (&vec![Position::F7], Position::F7),
            (&vec![Position::A8], Position::A8),
            (&vec![Position::A5, Position::B2], Position::A5),
            (&vec![Position::C1, Position::D1, Position::D2], Position::D2),
            (&vec![Position::F2, Position::B1, Position::G4], Position::G4),
            (&vec![Position::E3, Position::E4, Position::A4], Position::A4),
        ]
        .iter()
        .enumerate()
        {
            let mut bitboard = Bitboard::empty();
            for &position in positions.iter() {
                bitboard.set(position);
            }
            let bitboard = bitboard;

            let expected = msb;
            let actual = bitboard.bitscan_reverse();

            assert_eq!(
                expected, actual,
                "Test {} failed. Expected {:?}, found {:?}",
                i, expected, actual
            );
        }

    }

    #[test]
    fn default_bitboard() {
        let bitboard = Bitboard::default();
        assert_eq!(0, bitboard.0);
    }

    #[test]
    fn bitboard_from_u64() {
        let bitboard = Bitboard::from(5915);
        assert_eq!(5915, bitboard.0);
    }

    #[test]
    fn bitboard_into_u64() {
        let bitboard = Bitboard(5915);
        assert_eq!(5915u64, bitboard.into());
    }

    #[test]
    fn bitboard_bitand() {
        assert_eq!(
            Bitboard::from(0b10001),
            Bitboard::from(0b11011) & Bitboard::from(0b10101)
        );
    }

    #[test]
    fn bitboard_bitand_u64() {
        assert_eq!(Bitboard::from(0b10001), Bitboard::from(0b11011) & 0b10101);
    }

    #[test]
    fn bitboard_bitand_assign() {
        let mut bitboard = Bitboard::from(0b01100);
        bitboard &= Bitboard::from(0b01001);
        assert_eq!(Bitboard::from(0b01000), bitboard);
    }

    #[test]
    fn bitboard_bitand_assign_u64() {
        let mut bitboard = Bitboard::from(0b01100);
        bitboard &= 0b01001;
        assert_eq!(Bitboard::from(0b01000), bitboard);
    }

    #[test]
    fn bitboard_bitor() {
        assert_eq!(
            Bitboard::from(0b11011),
            Bitboard::from(0b11000) | Bitboard::from(0b00011)
        );
    }

    #[test]
    fn bitboard_bitor_u64() {
        assert_eq!(Bitboard::from(0b11011), Bitboard::from(0b11000) | 0b00011);
    }

    #[test]
    fn bitboard_bitor_assign() {
        let mut bitboard = Bitboard::from(0b01000);
        bitboard |= Bitboard::from(0b00100);
        assert_eq!(Bitboard::from(0b01100), bitboard);
    }

    #[test]
    fn bitboard_bitor_assign_u64() {
        let mut bitboard = Bitboard::from(0b01000);
        bitboard |= 0b00100;
        assert_eq!(Bitboard::from(0b01100), bitboard);
    }

    #[test]
    fn bitboard_bitxor() {
        assert_eq!(
            Bitboard::from(0b10001),
            Bitboard::from(0b10101) ^ Bitboard::from(0b00100),
        )
    }

    #[test]
    fn bitboard_bitxor_u64() {
        assert_eq!(Bitboard::from(0b10001), Bitboard::from(0b10101) ^ 0b00100)
    }

    #[test]
    fn bitboard_bitxor_assign() {
        let mut bitboard = Bitboard::from(0b11011);
        bitboard ^= Bitboard::from(0b01110);
        assert_eq!(Bitboard::from(0b10101), bitboard);
    }

    #[test]
    fn bitboard_bitxor_assign_u64() {
        let mut bitboard = Bitboard::from(0b11011);
        bitboard ^= 0b01110;
        assert_eq!(Bitboard::from(0b10101), bitboard);
    }

    #[test]
    fn bitboard_shl() {
        assert_eq!(Bitboard::from(0b1000), Bitboard::from(1) << 3);
    }

    #[test]
    fn bitboard_shl_assign() {
        let mut bitboard = Bitboard::from(0b010);
        bitboard <<= 5;
        assert_eq!(Bitboard::from(0b1000000), bitboard);
    }

    #[test]
    fn bitboard_shr() {
        assert_eq!(Bitboard::from(1), Bitboard::from(0b1000) >> 3);
    }

    #[test]
    fn bitboard_shr_assign() {
        let mut bitboard = Bitboard::from(0b1000000);
        bitboard >>= 5;
        assert_eq!(Bitboard::from(0b10), bitboard);
    }

    #[test]
    fn bitboard_not() {
        assert_eq!(Bitboard::from(1), !Bitboard::from(0xfffffffffffffffe));
    }

    #[test]
    fn bitboard_eq() {
        assert_eq!(Bitboard::from(59), Bitboard::from(59));
    }

    #[test]
    fn bitboard_ne() {
        assert_ne!(Bitboard::from(59), Bitboard::from(15));
    }
}
