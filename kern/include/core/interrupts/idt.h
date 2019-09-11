#pragma once
#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define SYSCALL_CODE 0x80

#define INTERRUPT_GATE_32 0x3
#define INTERRUPT_GATE_16 0x6
#define TRAP_GATE_32 0xF
#define TRAP_GATE_16 0x7
#define TASK_GATE_32 0x5

struct interrupt_desc_table
{
    uint16_t len;
    uint32_t addr;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t first_offset;
    uint16_t gdt_selector;
    uint8_t zero; // = 0
    uint8_t flags; // = Ob00001110
    uint16_t second_offset;
} __attribute__((packed));

typedef struct interrupt_desc_table idt_t;
typedef struct idt_ptr idt_entry_t;

#define ISR_NOERRCODE(n) \
    extern void isr_##n()

ISR_NOERRCODE(0);
ISR_NOERRCODE(1);
ISR_NOERRCODE(2);
ISR_NOERRCODE(3);
ISR_NOERRCODE(4);
ISR_NOERRCODE(5);
ISR_NOERRCODE(6);
ISR_NOERRCODE(7);
ISR_NOERRCODE(8);
ISR_NOERRCODE(9);
ISR_NOERRCODE(10);
ISR_NOERRCODE(11);
ISR_NOERRCODE(12);
ISR_NOERRCODE(13);
ISR_NOERRCODE(14);
ISR_NOERRCODE(15);
ISR_NOERRCODE(16);
ISR_NOERRCODE(17);
ISR_NOERRCODE(18);
ISR_NOERRCODE(19);
ISR_NOERRCODE(20);
ISR_NOERRCODE(21);
ISR_NOERRCODE(22);
ISR_NOERRCODE(23);
ISR_NOERRCODE(24);
ISR_NOERRCODE(25);
ISR_NOERRCODE(26);
ISR_NOERRCODE(27);
ISR_NOERRCODE(28);
ISR_NOERRCODE(29);
ISR_NOERRCODE(30);
ISR_NOERRCODE(31);
ISR_NOERRCODE(32);

extern uint8_t enable_idt();

#endif