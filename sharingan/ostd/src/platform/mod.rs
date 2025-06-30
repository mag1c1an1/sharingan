mod aarch64 {
    mod boot {
        type A64PTE = u64;

        #[unsafe(link_section = ".data.boot_page_table")]
        static mut BOOT_PT_L0: [A64PTE; 512] = [0; 512];

        #[unsafe(link_section = ".data.boot_page_table")]
        static mut BOOT_PT_L1: [A64PTE; 512] = [0; 512];

        unsafe extern "C" fn _start_primary() -> ! {
            todo!()
        }

        unsafe extern "C" fn _start_secondary() -> ! {
            todo!()
        }
    }
}
