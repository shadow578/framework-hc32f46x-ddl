# Boot Mode Configuration

firmware binaries for HC32F460 Series MCUs include a special **ICG** (**I**nitialisation **C**onfi**g**uration) section, which is used to configure the chip on reset.
this section is only used when booting *without* a bootloader, and is not needed when booting *with* a bootloader.

the `boot_mode` option allows you to choose between two modes:

1. `primary`: the ICG section is included, and the firmware supports booting with _OR_ without a bootloader. This is the default.
2. `secondary`: the ICG section is not included, and the firmware can only be booted with a bootloader. This saves about 1.5k of flash space.

> [!NOTE]
> if you are unsure which mode to use, use `primary`.
> the `primary` boot mode still supports booting with a bootloader, only the other way around is not supported.

> [!CAUTION]
> do not attempt to boot a firmware with `boot_mode=secondary` without a bootloader.
> since there will be code in the ICG section, the chip may be configured incorrectly.
> this could cause anything from weird behaviour to the chip being permanently damaged.


## Setting the Boot Mode

the `boot_mode` option can be set in the board definition file, or in the `platformio.ini` file.

platformio.ini:
```ini
[env:my_env]
# ...
board_build.boot_mode = secondary
```
