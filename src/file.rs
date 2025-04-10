pub type File = u8;

/// Wraps the given file to be represented by a debug formatter.
pub struct FileWrapper(File);

pub const A: File = 0;
pub const B: File = 1;
pub const C: File = 2;
pub const D: File = 3;
pub const E: File = 4;
pub const F: File = 5;
pub const G: File = 6;
pub const H: File = 7;

impl std::fmt::Debug for FileWrapper {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{}",
            match self.0 {
                0 => 'A',
                1 => 'B',
                2 => 'C',
                3 => 'D',
                4 => 'E',
                5 => 'F',
                6 => 'G',
                7 => 'H',
                _ => unreachable!(),
            }
        )
    }
}
