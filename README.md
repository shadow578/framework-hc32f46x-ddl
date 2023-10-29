# PlatformIO support for HUADA HC32F460 Series DDL

This repository contains the [HUADA HC32F460 Series DDL](https://www.hdsc.com.cn/Category83-1487), adapted to work with platformio and [the hc32f46x platform](https://github.com/shadow578/platform-hc32f46x).

Primary usage is for [Marlin](https://github.com/shadow578/Marlin-H32), tho other use cases should work too.

Mapping of HUADA DDL files to the files in this repository can be found in [docs/FILES_MAPPING.md](docs/FILES_MAPPING.md).
More details on the patches applied to the DDL can be found in [docs/PATCHES.md](docs/PATCHES.md).

# Notice

this framework is still in development, and not yet ready for production use. expect things to break over time.

# Configuration Options

## linker script options

the linker script can be configured in the platformio environment using options in `board_build`.
options are **directly** passed to the linker script using the `--defsym` option.

| option        | description                           | default value |
| ------------- | ------------------------------------- | ------------- |
| `flash_start` | the start address of the flash memory | `0x0`         |
| `flash_size`  | the size of the flash memory          | `256K`        |
| `boot_mode`   | firmware boot mode                    | `primary`     |
| `preprocess`  | enable linker script preprocessing    | `true`        |

> [!NOTE]
> linker script options can either be set in the board definition file, or in the platformio.ini file.

> [!NOTE]
> the build script will automatically calculate the end of flash memory based on the start address and size.

> [!WARNING]
> linker script options undergo a basic validation, but you should still make sure you pass sensible values.

> [!IMPORTANT]
> do not set `preprocess=false` unless you're using a custom linker script.
> the default linker script is generated from the options passed to the linker, and disabling preprocessing will cause the build to fail.

### board definition

```json
{
  // ...
  "build": {
    // ...
    "ld_args": {
      "flash_start": "0x00000000",
      "flash_size": "256K"
    }
  }
}
```

### platformio.ini

```ini
[env:myenv]
# ...
board_build.ld_args.flash_start = 0x0000C000
board_build.ld_args.flash_size = 256K
board_build.ld_args.boot_mode = primary
```

### boot mode

firmware on the hc32f46x includes a special "ICG" (**I**nitialisation **C**onfi**g**uration) section, which is used to configure the chip on reset. to include this section, a considerable amount of flash space is used as padding.
But there is no need to include the ICG section if you're booting using a bootloader, since it is only used on reset.

the `boot_mode` option allows you to choose between two modes:

1. `primary`: the ICG section is included, and the firmware supports booting with _OR_ without a bootloader. This is the default.
2. `secondary`: the ICG section is not included, and the firmware can only be booted with a bootloader. This saves about 1.5k of flash space.

> [!NOTE]
> the `primary` boot mode still supports booting with a bootloader, only the other way around is not supported.
> If you are unsure which mode to use, use `primary`.

> [!IMPORTANT]
> do not attempt to boot a firmware with `boot_mode=secondary` without a bootloader.
> since there will be code in the ICG section, the chip may be configured incorrectly.
> this could cause anything from the chip not booting, to the chip being damaged.

## extra build flags

the core allows adding extra build flags to build commands. Available options are:

- `board_build.flags.common`: added to all build commands
- `board_build.flags.c`: added to C build commands only
- `board_build.flags.cpp`: added to C++ build commands only
- `board_build.flags.asm`: added to assembly build commands only
- `board_build.flags.link`: added to linker commands only

```ini
[env:myenv]
# ...
board_build.flags.cpp =
	-fno-threadsafe-statics
	-fno-exceptions
```

> [!IMPORTANT]
> only set extra build flags if you know what you're doing.

## DDL options

drivers in the ddl library must be enabled before they can be used. this is done by setting the `ddl` option in the board configuration, either in the board definition file, or in the platformio.ini file.
drivers not specified will be disabled by default.

| option             | description                                             |
| ------------------ | ------------------------------------------------------- |
| `print`            | ddl printf functionality, directed to a dedicated usart |
| `adc`              | analog to digital converter driver (ADC)                |
| `aes`              | AES (encryption / decryption) driver                    |
| `can`              | can bus driver                                          |
| `cmp`              | on-chip analog comparator driver                        |
| `clk`              | clock generator driver                                  |
| `dcu`              | data computing unit driver                              |
| `dmac`             | DMA controller driver                                   |
| `efm`              | Embedded Flash Memory driver                            |
| `emb`              | Emergency / Software Brake mode driver                  |
| `event_port`       | Event Port driver                                       |
| `extint`           | external interrupt driver                               |
| `gpio`             | gpio driver                                             |
| `hash`             | hash driver                                             |
| `i2c`              | i2c peripheral driver                                   |
| `i2s`              | i2s peripheral driver                                   |
| `interrupts`       | interrupt controller driver                             |
| `interrupts_share` | ?                                                       |
| `keyscan`          | keyboard matrix scan driver                             |
| `mpu`              | Memory Protection Unit (?) driver                       |
| `ots`              | on-chip temperature sensor driver                       |
| `pwc`              | power controller driver                                 |
| `qspi`             | quad spi peripheral driver                              |
| `rmu`              | Reset Management Unit driver                            |
| `rtc`              | Real Time Clock driver                                  |
| `sdioc`            | sdio peripheral driver                                  |
| `spi`              | spi peripheral driver                                   |
| `sram`             | sram driver                                             |
| `swdt`             | special watchdog timer driver                           |
| `timer0`           | timer0 driver                                           |
| `timer4.cnt`       | timer4 counter driver                                   |
| `timer4.emb`       | timer4 emergency brake driver                           |
| `timer4.oco`       | timer4 compare output driver                            |
| `timer4.pwm`       | timer4 pwm driver                                       |
| `timer4.sevt`      | timer4 special event driver                             |
| `timer6`           | timer6 driver                                           |
| `timera`           | timerA driver                                           |
| `trng`             | true random number generator driver                     |
| `usart`            | usart peripheral driver                                 |
| `wdt`              | watchdog timer driver                                   |

> Note: ddl drivers can be included either with `#include "hc32_ddl.h"` or `#include "hc32f46x_<driver>.h"`

> Note: while this list should be up-to-date, you can always check in [ddl_options.py](./tools/platformio/ddl_options.py) for the latest.

### board definition

```json
{
  // ...
  "build": {
    // ...
    "ddl": {
      "adc": "true",
      "aes": "false"
    }
  }
}
```

### platformio.ini

```ini
[env:myenv]
# ...
board_build.ddl.adc = true
board_build.ddl.aes = false
```

## Middleware options

middleware placed in `middleware/` must be enabled before they can be used. this is done by setting the `mw` option in the board configuration, either in the board definition file, or in the platformio.ini file.
middleware not specified will be disabled by default.

| middleware name | description                    |
| --------------- | ------------------------------ |
| `sd_card`       | sd card / sdmmc middleware     |
| `w25qxx`        | w25qxx flash memory middleware |
| `wm8731`        | wm8731 audio codec middleware  |

> Note: middleware is added to the include path, and can be included with `#include "<middleware_header>.h"`

> Note: while this list should be up-to-date, you can always check the [middleware directory](./middleware) for the latest.

### board definition

```json
{
  // ...
  "build": {
    // ...
    "mw": {
      "sd_card": "true"
    }
  }
}
```

### platformio.ini

```ini
[env:myenv]
# ...
board_build.mw.sd_card = true
```
