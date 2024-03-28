#include "startup.h"

// check expected size of vector table
static_assert(sizeof(irq_vector_t) == 4, "irq_vector_t must be 4 bytes");
static_assert(sizeof(uint32_t *) == 4, "uint32_t must be 4 bytes");
static_assert(sizeof(vector_table) == (16 + 144) * 4, "vector_table does not match expected size");
