# Flash Size and Application Offset Configuration

the flash size and application offset can be configured using the `upload.maximum_size` and `upload.offset_address` options.

| Option                  | Default  | Description                      |
| ----------------------- | -------- | -------------------------------- |
| `upload.maximum_size`   | `262144` | the size of the flash            |
| `upload.offset_address` | `0`      | application start offset address |


## Setting the Flash size and Application offset

platformio.ini:
```ini
[env:myenv]
# ...
board_upload.maximum_size = 262144
board_upload.offset_address = 0xC000
```
