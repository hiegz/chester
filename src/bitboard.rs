use crate::square::Square;
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

/// Creates a bitboard with given squares set.
#[macro_export]
macro_rules! brd {
    ( $( $bit:expr ),* $(,)? ) => {{
        #[allow(unused_mut)]
        let mut bitboard: u64 = 0;
        $(
            bitboard |= 1 << $bit;
        )*
        bitboard
    }};
}

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

/// Removes the first least significant bit and returns its position.
///
/// In debug mode, this function asserts that the bitboard is not empty.
pub fn pop_first(bitboard: &mut Bitboard) -> Square {
    debug_assert!(!is_empty(*bitboard));
    let index = self::bitscan_forward(*bitboard);
    *bitboard = *bitboard ^ (1 << index);
    return index;
}

/// Returns the position of the first least significant set bit.
///
/// In debug mode, this function asserts that the bitboard is not empty.
pub fn bitscan_forward(bitboard: Bitboard) -> Square {
    debug_assert!(!is_empty(bitboard));
    return bitboard.trailing_zeros() as Square;
}

/// Removes the first most significant bit and returns its position.
///
/// In debug mode, this function asserts that the bitboard is not empty.
pub fn pop_last(bitboard: &mut Bitboard) -> Square {
    debug_assert!(!is_empty(*bitboard));
    let index = self::bitscan_reverse(*bitboard);
    *bitboard = *bitboard ^ (1 << index);
    return index;
}

/// Returns the position of the first most significant set bit.
///
/// In debug mode, this function asserts that the bitboard is not empty.
pub fn bitscan_reverse(bitboard: Bitboard) -> Square {
    debug_assert!(!is_empty(bitboard));
    return 63 - bitboard.leading_zeros() as Square;
}

/// Returns a powerset of the given bitboard.
///
/// Example:
///     Input: 101
///     Output [000, 001, 100, 101]
pub fn powerset(bitboard: Bitboard) -> Vec<Bitboard> {
    powerset_with_cardinality(bitboard, self::cardinality(bitboard))
}

/// Variant of `bitboard::powerset` that takes the bitboard's cardinality as an argument,
/// avoiding the need to compute it internally.
///
/// In debug mode, this function verifies that the provided cardinality matches the actual
/// number of set bits in the input bitboard.
pub fn powerset_with_cardinality(bitboard: Bitboard, cardinality: usize) -> Vec<Bitboard> {
    debug_assert!(self::cardinality(bitboard) == cardinality);
    let mut ret = Vec::with_capacity(cardinality);
    for index in 0..(1 << cardinality) {
        let mut b: Bitboard = bitboard;
        let mut r: Bitboard = 0;
        for i in 0..cardinality {
            let j = self::pop_first(&mut b);
            if index & (1 << i) != 0 {
                r |= 1 << j;
            }
        }
        ret.push(r);
    }
    return ret;
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
    use crate::brd;
    use crate::square;

    use std::collections::HashSet;

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
        for (i, &(bitboard, is_single)) in [
            (brd![square::C6], true),
            (brd![square::B1], true),
            (brd![square::A8], true),
            (brd![square::H1], true),
            (brd![square::B1, square::B2], false),
            (brd![square::A2, square::D8], false),
            (brd![square::H1, square::A8, square::D5], false),
        ]
        .iter()
        .enumerate()
        {
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
        for (i, &(bitboard, cardinality)) in [
            (brd![], 0),
            (brd![square::C6], 1),
            (brd![square::B1], 1),
            (brd![square::A8], 1),
            (brd![square::H1], 1),
            (brd![square::B1, square::B2], 2),
            (brd![square::A2, square::D8], 2),
            (brd![square::H1, square::A8, square::D5], 3),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(
                cardinality,
                bitboard::cardinality(bitboard),
                "Test case #{} failed",
                i,
            );
        }
    }

    #[test]
    fn pop_first() {
        for (i, &(mut before, after, index)) in [
            (brd![square::A1], brd![], square::A1),
            (brd![square::G8], brd![], square::G8),
            (brd![square::H8], brd![], square::H8),
            (brd![square::A1, square::A4], brd![square::A4], square::A1),
            (brd![square::H4, square::A3], brd![square::H4], square::A3),
            (brd![square::B5, square::C5], brd![square::C5], square::B5),
            (brd![square::H7, square::H8], brd![square::H8], square::H7),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(
                index,
                bitboard::pop_first(&mut before),
                "Test case #{} failed (incorrect square index)",
                i
            );
            assert_eq!(after, before, "Test case #{} failed (bitboards differ)", i);
        }
    }

    #[test]
    #[rustfmt::skip]
    fn bitscan_forward() {
        for (i, &(bitboard, lsb)) in [
            (brd![square::H1], square::H1),
            (brd![square::A1], square::A1),
            (brd![square::G2], square::G2),
            (brd![square::F7], square::F7),
            (brd![square::A8], square::A8),
            (brd![square::A5, square::B2], square::B2),
            (brd![square::C1, square::D1, square::D2], square::C1),
            (brd![square::F2, square::B1, square::G4], square::B1),
            (brd![square::E3, square::E4, square::A4], square::E3),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(
                lsb, bitboard::bitscan_forward(bitboard),
                "Test case #{} failed",
                i
            );
        }
    }

    #[test]
    fn pop_last() {
        for (i, &(mut before, after, index)) in [
            (brd![square::A1], brd![], square::A1),
            (brd![square::G8], brd![], square::G8),
            (brd![square::H8], brd![], square::H8),
            (brd![square::A1, square::A4], brd![square::A1], square::A4),
            (brd![square::H4, square::A3], brd![square::A3], square::H4),
            (brd![square::B5, square::C5], brd![square::B5], square::C5),
            (brd![square::H7, square::H8], brd![square::H7], square::H8),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(
                index,
                bitboard::pop_last(&mut before),
                "Test case #{} failed (incorrect square index)",
                i
            );
            assert_eq!(after, before, "Test case #{} failed (bitboards differ)", i);
        }
    }

    #[test]
    #[rustfmt::skip]
    fn bitscan_reverse() {
        for (i, &(bitboard, msb)) in [
            (brd![square::H1], square::H1),
            (brd![square::A1], square::A1),
            (brd![square::G2], square::G2),
            (brd![square::F7], square::F7),
            (brd![square::A8], square::A8),
            (brd![square::A5, square::B2], square::A5),
            (brd![square::C1, square::D1, square::D2], square::D2),
            (brd![square::F2, square::B1, square::G4], square::G4),
            (brd![square::E3, square::E4, square::A4], square::E4),
        ]
        .iter()
        .enumerate()
        {
            assert_eq!(
                msb, bitboard::bitscan_reverse(bitboard),
                "Test case #{} failed",
                i
            );
        }
    }

    #[test]
    fn powerset() {
        for (i, (bitboard, powerset)) in [
            (brd![], vec![brd![]]),
            (brd![square::D5], vec![brd![], brd![square::D5]]),
            (
                brd![square::D5, square::G2],
                vec![
                    brd![],
                    brd![square::D5],
                    brd![square::G2],
                    brd![square::D5, square::G2],
                ],
            ),
        ]
        .iter()
        .enumerate()
        {
            let bitboard = *bitboard;
            let expected = powerset;
            let actual = bitboard::powerset(bitboard);

            let set_a: HashSet<_> = expected.iter().collect();
            let set_b: HashSet<_> = actual.iter().collect();

            assert_eq!(set_a, set_b, "Test case #${} failed", i);
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
