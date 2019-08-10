.set MAGIC, 0x1badb002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .text
    jmp _start
    
    .align 4
     
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

    .global load
    .global _start
    .global enablePaging
    
    .extern kMain
    .extern puts
    .extern err_code1
    .extern err_codeU

    .align 4
    
_start:
    cli     /* We disable interrupts */

    movl $stack, %esp
    
    movl %eax, boot_data_multibootptr
    movl %ebx, boot_data_magicptr

    /* The following enables long mode. We aren't going to enable this for the moment, as this is
       for the moment a 32-bit kernel. */
    /*
     * mov 0xc0000080, %ecx // Select MSR's register 0xc0000080 (EFER)
     * rdmsr                // read the register
     * or 0b10000000, %eax  // Change the bit of the long mode to 1
     * wrmsr                // write the register
     */

    /* We load our GDT descriptor table pointing to the actual GDT */
    lgdt glob_desc_table
    /* We need to first set the CS segment to the second entry of the GDT. Since there is no such instruction,
       we do a short segmented jump instead. */
    ljmp $0x08, $main

main:
    /* We set the rest of the segments to the third entry of the GDT. */
    movw $0x10, %ax
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %ds
    movw %ax, %fs
    movw %ax, %gs
    
    /* We push our structure into the stack and call our `kMain` function */
    pushl boot_data
    call kMain
    
    /* If we have reached this part of the code, we can safely say that the kernel has errored out, since it
       is not supposed to do that. */
    movl %eax, %edi
    call handleReturn
    
    /* We create an infinite loop from there: */
    _infL:
        hlt       /* We halt the processor. Some motheboards may ignore this instruction, and thus... */
        jmp _infL /* we loop infinitely, which properly "blocks" the processor just in case. */
        
/* This is a simple error handler. It will be probably rewritten, but for the moment we just use this as a
   working placeholder. */
handleReturn:
    /* Pretty simple code that behaves the same as a `if` in C. */
    cmp $1, %edi

    /* We wanna write this in red to represent how much dramatic the situation is. */
    movb $0x0c, %ah

    je hr_code1
    jne hr_codeU
    
    hr_code1:
        movl $err_code1, %esi
        jmp hr_end
        
    hr_codeU:
        movl $err_codeU, %esi
        jmp hr_end
        
    hr_end:
        call puts
        
        xor %esi, %esi
        xor %edi, %edi
        ret
    
.section .data        
    gdt_ptr:
        gdt_ptr_null:
            .quad 0
        gdt_ptr_code:
            .word 0xffff     /* segment size limit */
            .word 0          /* first base (bit #0 -> #15) */
            .byte 0          /* second base (bit #16 -> #23) */
            .byte 0x9a       /* access byte */
            .byte 0b11001111 /* high 4 bits (flags) ; low 4 bits (limit 4 last bits)(limit is 20 bit wide) */
            .byte 0          /* third base (bit #24 -> #31) */
        gdt_ptr_data:
            .word 0xffff     /* segment size limit */
            .word 0          /* first base (bit #0 -> #15) */
            .byte 0          /* second base (bit #16 -> #23) */
            .byte 0x92       /* access byte */
            .byte 0b11001111 /* high 4 bits (flags) ; low 4 bits (limit 4 last bits)(limit is 20 bit wide) */
            .byte 0          /* third base (bit #24 -> #31) */
    gdt_end:
            
    boot_data:
        boot_data_magicptr:      .long 0 /* stored in ebx when booting */
        boot_data_multibootptr:  .long 0 /* stored in eax when booting */
        
    glob_desc_table:
        glob_desc_table_size:    .word gdt_end - gdt_ptr - 1
        glob_desc_table_ptr:     .long gdt_ptr
    
.section .bss
    .space 1024*1024    /* 1 MiB */
    stack:
