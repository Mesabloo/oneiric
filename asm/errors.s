.section .rodata
    .global err_code1
    .global err_code2
    .global err_code4
    .global err_codeU

    err_code1: .asciz "Panic! Internal error occured: code 0b00000001 - Kernel exited unexpectedly. "
    err_code2: .asciz "Panic! Internal error occured: code 0b00000010 - No multiboot data available. "
    err_code4: .asciz "Panic! Internal error occured: code 0b00000100 - Incorrect multiboot data. "
    err_codeU: .asciz "Panic! Internal error occured: unknown code. "
