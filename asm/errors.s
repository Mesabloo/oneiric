.section .rodata
    .global err_should_not_be_reached
    err_should_not_be_reached: .asciz "the kernel has errorred out and has reached code which shouldn't be reached..."
