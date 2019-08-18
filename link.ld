ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
    padding = 0xC0000000;
    . = padding + 0x00100000;
    startKernel = .;
    .multiboot : AT(ADDR(.multiboot) - padding)
    {
        *(.multiboot*)
    }

    .text : AT(ADDR(.text) - padding)
    {
        *(.text*)
    }

    .data : AT(ADDR(.data) - padding)
    {
        *(.data*)
    }

    .rodata : AT(ADDR(.rodata) - padding)
    {
        *(.rodata*)
    }

    .bss : AT(ADDR(.bss) - padding)
    {
        *(.bss)
    }

    . = ALIGN(0x1000);
    endKernel = .;

    /DISCARD/ :
    {
        *(.comment)
    }
}

