#ifndef __MEMORY_UTILS_H__
#define __MEMORY_UTILS_H__
#include <stdint.h>
#include "startup.h"

/**
 * @brief get current heap base
 */
extern "C" char *_sbrk(int incr);

/**
 * @brief get the current stack pointer
 * @return the current stack pointer
 */
static inline void *get_stack_pointer()
{
    register void *sp asm("sp");
    return sp;
}

/**
 * @brief get the total available stack space
 * @return the total stack space in bytes
 */
static inline size_t get_total_stack_space()
{
    return (size_t)&__StackTop - (size_t)&__StackLimit;
}

/**
 * @brief get the free stack space
 * @return the free stack space in bytes
 */
static inline size_t get_free_stack_space()
{
    return (size_t)get_stack_pointer() - (size_t)&__StackLimit;
}

/**
 * @brief get the total heap space
 * @return the total heap space in bytes
 */
static inline size_t get_total_heap_space()
{
    return (size_t)&__HeapLimit - (size_t)&__HeapBase;
}

/**
 * @brief get the total available heap space
 * @return the total heap space in bytes
 */
static inline size_t get_free_heap_space()
{
    return (size_t)&__HeapLimit - (size_t)_sbrk(0);
}

#endif // __MEMORY_UTILS_H__
