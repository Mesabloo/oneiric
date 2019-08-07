.section .text
    .global puts
    
puts:
    pushl %ebx
    movl $0xb8000, %edi
    cld

    puts.loop:
        lodsb
        cmpb $0, %al
        jz puts.end
        stosw
        jmp puts.loop

    puts.end:
        popl %ebx
        retl

.section .rodata
    .global err_code1
    .global err_codeU

    err_code1: .asciz "Panic! Internal error occured: code 1 - Kernel exited unexpectedly."
    err_codeU: .asciz "Panic! Internal error occured: unknown code."
