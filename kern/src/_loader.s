.set MULTIBOOT_MAGIC_NUMBER, 0x1BADB002
.set MULTIBOOT_FLAGS, (1 << 0 | 1 << 1 | 1 << 2)
.set MULTIBOOT_CHECKSUM , -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS)
.set MULTIBOOT_STRUCT_LENGTH, 118

.set KERNEL_VIRTUAL_BASE, 0xC0000000
.set KERNEL_PHYSICAL_BASE, 0x00100000

.section .multiboot
multiboot_header:
    .align 4
    .long MULTIBOOT_MAGIC_NUMBER
    .long MULTIBOOT_FLAGS
    .long MULTIBOOT_CHECKSUM

    .long 0
    .long 0
    .long 0
    .long 0
    .long 0 /* Ignore those 5 values, flags[16] is not set */

    .long 1   /* EGA-standard text mode, 0 is the graphical mode */
    .long 90  /* Preferred width (in pixels for graphical mode, in characters for text mode) */
    .long 60  /* Preferred height (in pixels for graphical mode, in characters for text mode) */
    .long 0   /* Preferred color depth. 0 if in text mode, else contains the number of bits per pixel */
/* end section .multiboot */

.section .text
    .align 4
    .global _start, start
    .extern terminate, kMain, initDisplay

_start: start:
    cld /* First clear the EFLAGS */
    movl $callstack_top, %esp /* Create the stack */

.check_magic_number:
    cmp $0x2BADB002, %eax /* Check if the magic number returned by GRUB is correct (no reason it wouldn't) */
    je .copy_multiboot_info

    movl $0x0432, 0xb8000
    movl $0x0442, 0xb8002
    movl $0x0441, 0xb8004
    movl $0x0444, 0xb8006

    L1:
        cli ; hlt
        jmp L1

.copy_multiboot_info:
    movl %ebx, %esi
    movl $(multiboot_info - KERNEL_VIRTUAL_BASE), %edi
    movl $MULTIBOOT_STRUCT_LENGTH, %ecx

    rep movsb /* We copy the multiboot header given by GRUB to a safe location */

.init_paging: /* Now we initiate paging */
    movl $(bootPT0 - KERNEL_VIRTUAL_BASE), %edi
    movl $1024, %ecx
    movl $0, %esi /* We create the first page table (we'll only need one at this stage) */
.L1:
    movl %esi, %edx
    orl $0x003, %edx
    movl %edx, (%edi)
.L2:
    addl $4096, %esi
    addl $4, %edi
    loop .L1 /* We map the first 4 MiB of memory to `0xC0000000` */
.L3:
    movl $(bootPD - KERNEL_VIRTUAL_BASE), %esi
    movl $(bootPT0 - KERNEL_VIRTUAL_BASE), (%esi)
    orl $0x003, (%esi) 

    addl $3072, %esi
    movl $(bootPT0 - KERNEL_VIRTUAL_BASE), (%esi)
    orl $0x003, (%esi)

    movl $(bootPD - KERNEL_VIRTUAL_BASE), %esi
    addl $4092, %esi
    movl $(bootPD - KERNEL_VIRTUAL_BASE), (%esi)
    orl $0x003, (%esi) /* We register the first page table in the page directory */

    movl $(bootPD - KERNEL_VIRTUAL_BASE), %edx
    movl %edx, %cr3

    movl %cr0, %edx
    orl $0x80010000, %edx
    movl %edx, %cr0 /* And we activate paging */

init:
    pushl $25
    pushl $80
    call initDisplay
    sub $0x8, %esp

    pushl $0xc00b8000
    call initDisplayBuffer
    sub $0x4, %esp

    lgdt glob_desc_table /* We load our Global Descriptor Table */

    ljmp $0x08, $init2 /* We initialize %cs */
init2:
    movw $0x10, %ax
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %ds
    movw %ax, %fs
    movw %ax, %gs /* And all the other segments needed for the GDT */

    invlpg 0 /* Invalidate the address 0 */

launch:
    pushl $multiboot_info
    call kMain /* And call the main function */
    subl $0x4, %esp

    pushl $0xe550

    end_loop:
        pushl $err_should_not_be_reached
        call terminate /* We terminate our kernel process with a RSOD (Red Screen Of Death) */
/* end section .text */

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
    glob_desc_table:
        glob_desc_table_size:    .word gdt_end - gdt_ptr - 1
        glob_desc_table_ptr:     .long gdt_ptr
/* end section .data */

.section .rodata
    err_should_not_be_reached: .asciz "the kernel has errorred out and has reached code which shouldn't be reached..."
/* end section .rodata */

.section .bss
    .align 4096
    bootPD: .space 4096  /* 4 KiB of space, for 1024 entries */
    bootPT0: .space 4096 /* 4 KiB of space, for 1024 entries */

    callstack_bottom:
    .space 1024*256 /* 256 kiB for the callstack, should be largely enough */
    callstack_top:

    .lcomm multiboot_info, 128 /* 128 bytes */
/* end section .bss */