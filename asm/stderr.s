.section .rodata
    .global err_code1
    .global err_codeU

    err_code1: .asciz "Panic! Internal error occured: code 1 - Kernel exited unexpectedly."
    err_codeU: .asciz "Panic! Internal error occured: unknown code."
