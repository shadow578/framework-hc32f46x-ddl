#include "startup.h"

#define __is_in_range(x, start, end) ((x) >= (start) && (x) < (end))

// expect the heap and stack to be outside of the .bss and .retbss sections
// - heap starts at __HeapBase and grows up to __HeapLimit
// - stack starts at __StackTop and grows down to __StackLimit
#define __is_in_bss(x) (__is_in_range(x, &__bss_start__, &__bss_end__) || __is_in_range(x, &__bss_start_ret_ram__, &__bss_end_ret_ram__))

static_assert(!__is_in_bss(&__HeapBase), "heap must not be in .bss or .retbss");
static_assert(!__is_in_bss(&__HeapLimit), "heap must not be in .bss or .retbss");
static_assert(!__is_in_bss(&__StackTop), "stack must not be in .bss or .retbss");
static_assert(!__is_in_bss(&__StackLimit), "stack must not be in .bss or .retbss");

// expect the heap and stack to not overlap
#define __is_in_heap(x) __is_in_range(x, &__HeapBase, &__HeapLimit)
#define __is_in_stack(x) __is_in_range(x, &__StackLimit, &__StackTop)

static_assert(!__is_in_heap(&__StackLimit), "heap and stack must not overlap");
static_assert(!__is_in_heap(&__StackTop), "heap and stack must not overlap");
static_assert(!__is_in_stack(&__HeapBase), "heap and stack must not overlap");
static_assert(!__is_in_stack(&__HeapLimit), "heap and stack must not overlap");

// check expected size of vector table
static_assert(sizeof(irq_vector_t) == 4, "irq_vector_t must be 4 bytes");
static_assert(sizeof(uint32_t *) == 4, "uint32_t must be 4 bytes");
static_assert(sizeof(vector_table) == (16 + 144) * 4, "vector_table does not match expected size");
