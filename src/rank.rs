pub type Rank = u8;

pub const ONE: Rank = 0;
pub const TWO: Rank = 1;
pub const THREE: Rank = 2;
pub const FOUR: Rank = 3;
pub const FIVE: Rank = 4;
pub const SIX: Rank = 5;
pub const SEVEN: Rank = 6;
pub const EIGHT: Rank = 7;

/// Wraps the given rank to be represented by a debug formatter.
#[derive(Eq, PartialEq)]
pub struct RankWrapper(pub Rank);

impl std::fmt::Debug for RankWrapper {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0 + 1,)
    }
}
