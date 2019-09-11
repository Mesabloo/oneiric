#include <core/interrupts/idt.h>
#include <std/stdmem.h>

static idt_t idt = { .len = 256, .addr = 0x0 };
static idt_entry_t entries[256];

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    entries[num].first_offset  = base & 0xFFFF;
    entries[num].second_offset = (base >> 16) & 0xFFFF;

    entries[num].gdt_selector  = sel;
    entries[num].zero          = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    entries[num].flags         = flags /* | 0x60 */;
}

/* extern */ uint8_t enable_idt()
{
    memset(entries, 0, sizeof(idt_entry_t) * 256);

    idt_set_gate(0, (uint32_t) isr_0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t) isr_1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t) isr_2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t) isr_3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t) isr_4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t) isr_5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t) isr_6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t) isr_7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t) isr_8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t) isr_9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t) isr_10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t) isr_11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t) isr_12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t) isr_13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t) isr_14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t) isr_15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t) isr_16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t) isr_17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t) isr_18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t) isr_19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t) isr_20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t) isr_21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t) isr_22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t) isr_23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t) isr_24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t) isr_25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t) isr_26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t) isr_27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t) isr_28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t) isr_29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t) isr_30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t) isr_31, 0x08, 0x8E);


    idt.addr = (uint32_t) &entries;
    idt.len = sizeof(idt_entry_t) * 256 - 1;
    asm inline("lidt idt");

    return 0;
}