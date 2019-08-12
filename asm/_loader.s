.set MAGIC, 0x1badb002
.set FLAGS, (1 << 0 | 1 << 1 | 1 << 16)
.set CHECKSUM, -(MAGIC + FLAGS)

multiboot_begin_addr:
.section .text
    jmp _start
    
    .align 4
     
multiboot_header:
    .long MAGIC /* Magic number, should be 0x1badb002 */
    .long FLAGS /* Flags, should at least have bit #0 and #1 set, bit #16 for addresses, and bit #2 for video information */
    .long CHECKSUM /* Checksum (= -(kernelMagic + flags)) where kernelMagic = 0x1badb002 */
.ifnb FLAGS & (1 << 16)
    .long multiboot_header /* Multiboot header start address (if bit #16 is set) */
    .long multiboot_begin_addr /* Kernel start load address (if bit #16 is set) */
    .long multiboot_end_addr /* Kernel end load address (if bit #16 is set) */
    .long stack /* .bss section end address (if bit #16 is set) */
    .long _start /* Kernel entry address (where to jump when starting) (if bit #16 is set) */
.endif
.ifnb FLAGS & (1 << 2)
    .long 1 /* Video mode type (0 == graphical, 1 == text) (if bit #2 is set) */
    .long 80 /* Screen width (if graphical, in pixels, else in characters) (if bit #2 is set) */
    .long 25 /* Screen height (if graphical, in pixels, else in characters) (if bit #2 is set) */
    .long 0 /* Screen depth (number of bits per pixel if in graphical mode, else 0) (if bit #2 is set) */
.endif

    .align 4

program:
    .global load
    .global _start
    
    .extern kMain
    .extern puts
    .extern err_code1
    .extern err_code2
    .extern err_code4
    .extern err_codeU
    
_start:
    cli     /* We disable interrupts */

    movl $stack, %esp
    
    movl %eax, boot_data_magicptr
    movl $multiboot_header, boot_data_kernelinfoptr
    movl %ebx, boot_data_multibootptr

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
    pushl boot_data_multibootptr
    pushl boot_data_kernelinfoptr
    pushl boot_data_magicptr
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

    cmp $0b1, %edi
    je hr_code1
    cmp $0b10, %edi
    je hr_code2
    cmp $0b100, %edi
    je hr_code4
    jne hr_codeU
    
    hr_code1:
        pushl $err_code1
        jmp hr_end
    hr_code2:
        pushl $err_code2
        jmp hr_end
    hr_code4:
        pushl $err_code4
        jmp hr_end
    hr_codeU:
        pushl $err_codeU
        jmp hr_end
        
    hr_end:
        /* We wanna write this in red to represent how much dramatic the situation is. */
        pushl $0x0c

        call puts

        xorl %edi, %edi
        add $0x8, %esp
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
        boot_data_magicptr:      .long 0 /* stored in eax when booting */
        boot_data_kernelinfoptr: .long 0
        boot_data_multibootptr:  .long 0 /* stored in ebx when booting */
        
    glob_desc_table:
        glob_desc_table_size:    .word gdt_end - gdt_ptr - 1
        glob_desc_table_ptr:     .long gdt_ptr
multiboot_end_addr:    

.section .bss
    .space 1024*1024*10    /* 10 MiB */
    stack:
