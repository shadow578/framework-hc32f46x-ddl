# Heap and Stack Configuration

the stack and heap sizes can be configured using the `board_build.stack_size` and `board_build.heap_size` options.


| Option                  | Default  | Description                      |
| ----------------------- | -------- | -------------------------------- |
| `board_build.stack_size` | `0x400` | the size of the stack |
| `board_build.heap_size`  | `0xC00` | the size of the heap  |


## Setting the Flash size and Application offset

platformio.ini:
```ini
[env:myenv]
# ...
board_build.stack_size = 0x400
board_build.heap_size = 0xC00
```

