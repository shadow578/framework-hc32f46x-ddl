#include "startup.h"

// expect the heap and stack to be outside of the .bss and .retbss sections
// - heap starts at __HeapBase and grows up to __HeapLimit
// - stack starts at __StackTop and grows down to __StackLimit
#define __is_in_range(x, start, end) ((x) >= (start) && (x) < (end))
#define __is_in_bss(x) (__is_in_range(x, &__bss_start__, &__bss_end__) || __is_in_range(x, &__bss_start_ret_ram__, &__bss_end_ret_ram__))

static_assert(!__is_in_bss(&__HeapBase), "heap must not be in .bss or .retbss");
static_assert(!__is_in_bss(&__HeapLimit), "heap must not be in .bss or .retbss");
static_assert(!__is_in_bss(&__StackTop), "stack must not be in .bss or .retbss");
static_assert(!__is_in_bss(&__StackLimit), "stack must not be in .bss or .retbss");
