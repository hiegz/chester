pub type Rank = u8;

/// Wraps the given rank to be represented by a debug formatter.
#[derive(Eq, PartialEq)]
pub struct RankWrapper(pub Rank);

impl std::fmt::Debug for RankWrapper {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0 + 1,)
    }
}
