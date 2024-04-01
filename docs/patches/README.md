# Patches to the DDL

to make the DDL work better with platformio, the arduino core, or marlin, some patches are applied.
these range from minor changes to adapt the ddl to the build system, to changes to make the ddl compile with a modern gcc version without warnings, to quality of life improvements.

## `hc32f46x_param.ld`

the linker script needs some adjustments to work with the platformio build system, mainly to support parameterisation of the flash start address and size.

note that the `DDL_STACK_SIZE` and `DDL_HEAP_SIZE` don't follow the naming pattern of the other parameters.
this is because they were added later and could not be changed without breaking backwards compatibility.

[patch](./hc32f46x_param.ld.patch)

## `hc32f460_can.h`

in the can ddl, a multi-line comment ends with a `\`, which gcc does not like...

[patch](./hc32f460_can.h.patch)

## `hc32f460_interrupts.c`

to allow for a more flexible interrupt configuration, all handlers are defined as weak symbols.

additionally, the `enIrqRegistration` and `enIrqResign` functions along with some other parts of the DDL are wrapped in a `#if !DDL_INTERRUPTS_CUSTOM_HANDLER_MANAGEMENT` block to allow for custom interrupt handler management.

[patch](./hc32f460_interrupts.c.patch)

## `hc32f460_pwc.h` + `hc32f460_pwc.c`

in the PWC ddl, the enum `en_pwc_stop_flash_sel` uses fairly generic names for the enum values, which may conflict with other code (namely Marlin).
to mitigate this, the enum values are prefixed with `Flash` to make them more unique.

[patch #1](./hc32f460_pwc.h.patch)
[patch #2](./hc32f460_pwc.c.patch)

## `hc32f460_timer0.c`

the timer0 driver creates a warning when compiled with a modern gcc version.
while it does work, this quiets the build process making it easier to spot actual errors.

<details>
<summary>Details</summary>

during reset of BCONR register, the original ddl code uses a bitfield `pstcTim0Reg->BCONR_f` cast to a uint32_t to clear the register. This causes a type-pruning warning.
To fix this, `pstcTim0Reg->BCONR_f` can be replaced with `pstcTim0Reg->BCONR` (which is the raw register value BCONR_f represents) in the register clear code.

Since the following code uses the value in the variable `stcBconrTmp`, it has to be set after the register clear code.

</details>

[patch](./hc32f460_timer0.c.patch)

## `hc32f460_usart.c`

to allow reduction of binary size, `addon_usart.h` provides access to individual functions to set the baud rate in different modes instead of the combined `USART_SetBaudrate` function.

to make the individual functions accessible, the definitions in `hc32f460_usart.c` must be changed to non-static

[patch](./hc32f460_usart.c.patch)

## `hc32f460_utility.h`

ddl has the option to use short file names in `DDL_ASSERT` messages to save flash space.
to allow for this, a macro `__SOURCE_FILE_NAME__` is defined by the build script and used in the `DDL_ASSERT` macro when `__DEBUG_SHORT_FILENAMES` is defined.

[patch](./hc32f460_utility.h.patch)
