.section .text
    .extern interrupt_handler

.macro ISR_NOERR n
    .global isr_\n
isr_\n\():
    cli
    pushl $0
    pushl $\n
    jmp isr_wrapper
.endm
.macro ISR_ERR n
    .global isr_\n
isr_\n\():
    cli
    pushl $\n
    jmp isr_wrapper
.endm

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_ERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_ERR 30
ISR_NOERR 31
ISR_NOERR 32

isr_wrapper:
    pushal   /* push %edi, %esi, %ebp, %esp, %ebx, %edx, %ecx, %eax */
    cld

    movw %ds, %ax 
    pushl %eax   /* save the data segment descriptor */
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call interrupt_handler

    popl %eax   /* reload the data segment descriptor */
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    popal    /* pop %edi, %esi, %ebp, %esp, %ebx, %edx, %ecx, %eax */
    addl $0x8, %esp

    sti
    iret
