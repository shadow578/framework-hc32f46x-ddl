# Linker Script Configuration

the linker script can be configured in the platformio environment using options in `board_build`.
options are **directly** passed to the linker script using the `--defsym` option.

| option        | description                           | default value |
| ------------- | ------------------------------------- | ------------- |
| `flash_start` | the start address of the flash memory | `0x0`         |
| `flash_size`  | the size of the flash memory          | `256K`        |
| `boot_mode`   | firmware boot mode                    | `primary`     |
| `preprocess`  | enable linker script preprocessing    | `true`        |

> [!TIP]
> the `flash_size` option describes the **total** size of the flash memory in bytes.
> do not subtract the bootloader size from the flash size, as this is done automatically by the build script.

> [!NOTE]
> the build script will automatically calculate the flash memory end address based on the start address and size.

> [!WARNING]
> while the linker script options undergo a basic validation, you should still make sure you pass sensible values.
> failing to do so may result in a build failure or unexpected behavior.

> [!CAUTION]
> disabling linker script preprocessing will cause the build to fail if the default linker script is used, or
> if the custom linker script requires preprocessing.


## Setting the Linker Script Options

the linker script options can be set in the board definition file, or in the platformio.ini file.


platformio.ini:
```ini
[env:my_env]
# ...
board_upload.offset_address = 0x0000C000
board_upload.maximum_size = 256K
board_build.boot_mode = primary
```


board.json:
```json
{
  // ...
  "upload": {
    "maximum_size": 262144,
    "maximum_ram_size": 192512,
    "offset_address": "0xc000"
  }
}
```
