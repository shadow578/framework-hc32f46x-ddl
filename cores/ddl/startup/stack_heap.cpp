#include <stdint.h>

#ifndef DDL_STACK_SIZE
#define DDL_STACK_SIZE 0x00000400
#endif

#ifndef DDL_HEAP_SIZE
#define DDL_HEAP_SIZE 0x00000C00
#endif

volatile char stack[DDL_STACK_SIZE] __attribute__((section(".stack"), aligned(8)));

volatile char heap[DDL_HEAP_SIZE] __attribute__((section(".heap"), aligned(8)));
