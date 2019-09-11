#pragma once
#ifndef HANDLER_H
#define HANDLER_H

#include <stdint.h>
#include <core/interrupts/dump.h>

extern void interrupt_handler(reg_dump_t dump);

#endif