# Heap and Stack Configuration

the stack and heap sizes can be configured using the `DDL_STACK_SIZE` and `DDL_HEAP_SIZE` options.

| Define           | Default | Description           |
| ---------------- | ------- | --------------------- |
| `DDL_STACK_SIZE` | `0x400` | the size of the stack |
| `DDL_HEAP_SIZE`  | `0xC00` | the size of the heap  |


## Setting the Stack and Heap Sizes

platformio.ini:
```ini
[env:myenv]
# ...
build_flags = 
    -D DDL_STACK_SIZE=0x800 # 2KB stack
    -D DDL_HEAP_SIZE=0x1000 # 4KB heap
```
