use core::fmt::{Arguments, Write};

struct Stdout;

impl Write for Stdout {
    fn write_str(&mut self, s: &str) -> core::fmt::Result {
        todo!()
    }
}


