#pragma once
#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <std/stddef.h>

typedef struct
{
    uint32_t magic;         // Magic number, should be 0x1badb002
    uint32_t flags;         // Flags, should at least have bit #0 and #1 set, bit #16 for addresses, and bit #2 for video information
    uint32_t checksum;      // Checksum (= -(kernelMagic + flags)) where kernelMagic = 0x1badb002
    uint32_t header_addr;   // Multiboot header start address (if bit #16 is set)
    uint32_t load_addr;     // Kernel start load address (if bit #16 is set)
    uint32_t load_end_addr; // Kernel end load address (if bit #16 is set)
    uint32_t bss_end_addr;  // .bss section end address (if bit #16 is set)
    uint32_t entry_addr;    // Kernel entry address (where to jump when starting) (if bit #16 is set)
    uint32_t mode_type;     // Video mode type (0 == graphical, 1 == text) (if bit #2 is set)
    uint32_t width;         // Screen width (if graphical, in pixels, else in characters) (if bit #2 is set)
    uint32_t height;        // Screen height (if graphical, in pixels, else in characters) (if bit #2 is set)
    uint32_t depth;         // Screen depth (number of bits per pixel if in graphical mode, else 0) (if bit #2 is set)
} MultibootInfo;

typedef struct
{
    // ?------------------------
    uint32_t flags;
    // ?--- flags & (1 << 0) ---
    uint32_t mem_lower;
    uint32_t mem_upper;
    // ?--- flags & (1 << 1) ---
    uint32_t boot_device;
    // ?--- flags & (1 << 2) ---
    uint32_t cmdline;
    // ?--- flags & (1 << 3) ---
    uint32_t mods_count;
    uint32_t mods_addr;
    // ?--- flags & (1 << 4) ---
    // ?  | flags & (1 << 5) ---
    uint32_t syms[3];
    // ?--- flags & (1 << 6) ---
    uint32_t mmap_length;
    uint32_t mmap_addr;
    // ?--- flags & (1 << 7) ---
    uint32_t drives_length;
    uint32_t drives_addr;
    // ?--- flags & (1 << 8) ---
    uint32_t config_table;
    // ?--- flags & (1 << 9) ---
    uint32_t boot_loader_name;
    // ?--- flags & (1 << 10) --
    uint32_t apm_table;
    // ?--- flags & (1 << 11) --
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    // ?--- flags & (1 << 12) --
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint8_t color_info[5];
} MultibootTable;

#endif