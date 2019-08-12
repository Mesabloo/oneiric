#pragma once

#ifndef KERNEL_H
#define KERNEL_H

#include <core/multiboot.h>

/**
 * Kernel entry point
 * Everything will launch from there
 */
extern int kMain(MultibootHeader* bootData);

#endif
