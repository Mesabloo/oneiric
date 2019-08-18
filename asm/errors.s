.section .rodata
    .global err_mmap_incorrect_length
    .global err_mb_incorrect_magic
    err_mmap_incorrect_length: .asciz "The memory map provided by GRUB is incorrectly length-ed!"
    err_mb_incorrect_magic: .asciz "The returned magic number is incorrect."
