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

impl BitAnd for Bitboard {
    type Output = Bitboard;

    fn bitand(self, rhs: Self) -> Self::Output {
        Bitboard::from(self.0.bitand(rhs.0))
    }
}

impl BitAndAssign for Bitboard {
    fn bitand_assign(&mut self, rhs: Self) {
        self.0.bitand_assign(rhs.0);
    }
}

impl BitOr for Bitboard {
    type Output = Bitboard;

    fn bitor(self, rhs: Self) -> Self::Output {
        Bitboard::from(self.0.bitor(rhs.0))
    }
}

impl BitOrAssign for Bitboard {
    fn bitor_assign(&mut self, rhs: Self) {
        self.0.bitor_assign(rhs.0);
    }
}

impl BitXor for Bitboard {
    type Output = Bitboard;

    fn bitxor(self, rhs: Self) -> Self::Output {
        Bitboard::from(self.0.bitxor(rhs.0))
    }
}

impl BitXorAssign for Bitboard {
    fn bitxor_assign(&mut self, rhs: Self) {
        self.0.bitxor_assign(rhs.0);
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
    fn empty_is_inverted_universal() {
        assert_eq!(Bitboard::empty(), !Bitboard::universal());
    }

    #[test]
    fn empty_is_not_single() {
        assert!(!(Bitboard::empty().is_single()));
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
    fn bitboard_bitand_assign() {
        let mut bitboard = Bitboard::from(0b01100);
        bitboard &= Bitboard::from(0b01001);
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
    fn bitboard_bitor_assign() {
        let mut bitboard = Bitboard::from(0b01000);
        bitboard |= Bitboard::from(0b00100);
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
    fn bitboard_bitxor_assign() {
        let mut bitboard = Bitboard::from(0b11011);
        bitboard ^= Bitboard::from(0b01110);
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
