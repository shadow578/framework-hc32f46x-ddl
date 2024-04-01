# Stack and Heap APIs

the DDL provides the following functions in the `startup/util.h` header:

| function                         | description                                                                               |
| -------------------------------- | ----------------------------------------------------------------------------------------- |
| `char *_sbrk(int incr)`          | access to libc sbrk                                                                       |
| `void *get_stack_pointer()`      | get the current stack pointer (slightly uncertain since this function may not be inlined) |
| `size_t get_total_stack_space()` | get total bytes available for the stack                                                   |
| `size_t get_free_stack_space()`  | get the currently free bytes of the stack                                                 |
| `size_t get_total_heap_space()`  | get total bytes available for the heap                                                    |
| `size_t get_free_heap_space()`   | get the currently free bytes of the heap                                                  |
