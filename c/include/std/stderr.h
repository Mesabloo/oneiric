#pragma once
#ifndef STDERR_H
#define STDERR_H

/**
 * Aborts the program, and prints the address of the last function call (which should be `call abort`)
 */
extern void abort();

/**
 * Asserts an expression is true, else aborts the program
 */
#ifdef DNDEBUG
#   define assert(e) ;
#else
    void assert(int e);
#endif

#endif