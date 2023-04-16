# framework-hc32f46x-ddl

platformio device driver library (ddl) framework for the hc32f46x, mainly for use with [marlin](https://github.com/shadow578/Marlin-H32).

# Notice

this platform is still in development, and is not yet ready for use. expect bugs, and expect things to break.

# Configuration Options

## linker script options

the linker script can be configured in the platformio environment using options in `board_build`.
options are **directly** passed to the linker script using the `--defsym` option.

| option          | description                           | example value (not actual values) |
| --------------- | ------------------------------------- | --------------------------------- |
| `flash_start`   | the start address of the flash memory | `0x0000`                          |
| `flash_size`    | the size of the flash memory          | `256K`                            |
| `ram_start`     | the start address of the ram          | `0x20000000`                      |
| `ram_size`      | the size of the ram                   | `64K`                             |
| `ram_ret_start` | the start address of retained ram     | `0x20010000`                      |
| `ram_ret_size`  | the size of retained ram              | `4K`                              |

> Note: the linker script will automatically calculate the locations of the memory sections.
> Note: parameters are **not** validated in any way, so make sure you pass sensible values.

these args can either be set in the board definition file, or in the platformio.ini file.

### board definition

```json
{
  // ...
  "build": {
    // ...
    "ld_args": {
      "flash_start": "0x00000000",
      "flash_size": "256K",
      "ram_start": "0x1FFF8000",
      "ram_size": "188K",
      "ram_ret_start": "0x200F0000",
      "ram_ret_size": "4K"
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
board_build.ld_args.ram_start = 0x1FFF8000
board_build.ld_args.ram_size = 188K
board_build.ld_args.ram_ret_start = 0x200F0000
board_build.ld_args.ram_ret_size = 4K
```

## DDL options

drivers in the ddl library must be enabled before they can be used. this is done by setting the `ddl` option in the board configuration, either in the board definition file, or in the platformio.ini file.
drivers not specified will be disabled by default.

| option             | description                                             |
| ------------------ | ------------------------------------------------------- |
| `print`            | ddl printf functionality, directed to a dedicated usart |
| `adc`              | analog to digital converter driver (ADC)                |
| `aes`              | aes driver                                              |
| `can`              | can bus driver                                          |
| `cmp`              | analog comparator driver                                |
| `clk`              | clock generator driver                                  |
| `dcu`              | data calculation unit driver                            |
| `dmac`             | DMA controller driver                                   |
| `efm`              | Embedded Flash Memory driver                            |
| `emb`              |
| `event_port`       |
| `extint`           | external interrupt driver                               |
| `gpio`             | gpio driver                                             |
| `hash`             | hash driver                                             |
| `i2c`              | i2c peripheral driver                                   |
| `i2s`              | i2s peripheral driver                                   |
| `interrupts`       | interrupt controller driver                             |
| `interrupts_share` |
| `keyscan`          | keyboard matrix scan driver                             |
| `mpu`              |
| `ots`              | on-chip temperature sensor driver                       |
| `pwc`              |
| `qspi`             | quad spi peripheral driver                              |
| `rmu`              |
| `rtc`              |
| `sdioc`            | sdio peripheral driver                                  |
| `spi`              | spi peripheral driver                                   |
| `sram`             | sram driver                                             |
| `swdt`             | special watchdog timer driver                           |
| `timer0`           | timer0 driver                                           |
| `timer4.cnt`       | timer4 counter driver                                   |
| `timer4.emb`       |
| `timer4.oco`       |
| `timer4.pwm`       | timer4 pwm driver                                       |
| `timer4.sevt`      |
| `timer6`           | timer6 driver                                           |
| `timera`           | timerA driver                                           |
| `trng`             | true random number generator driver                     |
| `usart`            | usart peripheral driver                                 |
| `usbfs`            | N/A                                                     |
| `wdt`              | watchdog timer driver                                   |

> Note: ddl drivers can be included either with `#include "hc32_ddl.h"` or `#include "hc32f46x_<driver>.h"`
> Note: some descriptions may be inaccurate.

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
