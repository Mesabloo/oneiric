#pragma once
#ifndef KERNEL_H
#define KERNEL_H

#include <core/multiboot.h>

extern void kMain(multiboot_info_t* mb_info);

#endif