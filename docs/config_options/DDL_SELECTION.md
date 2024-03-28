# Device Driver Selection

device drivers (also referred to as DDL(s)) are the core of the HC32F460 DDL framework. 
they provide C functions to interact with the hardware peripherals of the HC32F460, and are used to configure and control the hardware.


## Enabling / Disabling Drivers

device drivers must be enabled before they can be used.
this is done by setting the `ddl` option in the board configuration, either in the board definition file, or in the platformio.ini file.

drivers not specified will be disabled by default.


platformio.ini:
```ini
[env:my_env]
# ...
board_build.ddl.adc = true
board_build.ddl.aes = false
```


board.json:
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


## Using the Drivers

once a driver is enabled, it can be used in the code by including either the `hc32_ddl.h` header file, or the specific driver header file.

```c
#include <hc32_ddl.h>

// ...
```


## List of Available Drivers

the following drivers are available in the HC32F460 DDL framework:

| device driver      | description                                             |
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
| `interrupts_share` | interrupt sharing driver, for IRQ#128-143               |
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
