# Patches to the DDL

to make the DDL work better with platformio, some patches are applied.
These range from minor changes to adapt the ddl to the build system, to changes to make the ddl compile with a modern gcc version without warnings.

## `/ld/hc32f46x_param.ld`

the linker script needs minor adjustments to work with the platformio build system, mainly to add support for setting the flash start address and size from the platformio build system.

### 1. Parameters Documentation

while not strictly necessary, it is nice to have the parameters documented in the linker script.
The following comment is added to the top of the linker script:

```cpp
/*
 * parameterized linker flag for the HC32F46x SOC.
 * flash size and start offset have to be set as symbols for the linker script, using
 * the '--defsym' ('-Wl,'--defsym=<SYMBOL_NAME>=<SYMBOL_VALUE>'') flag.
 *
 * note: previously, ram options were also configurable.
 * this was removed to simplify the linker script (all HC32F460 have the same ram anyway)
 */

/* FLASH_START = 0x00000000; */
/* FLASH_SIZE = 256K; */
```

### 2. Flash Start Address and Size

to set the flash start address, the memory region `FLASH` is updated to use the `FLASH_START` symbol as ORIGIN and the `FLASH_SIZE` symbol as LENGTH:

```cpp
MEMORY
{
    FLASH       (rx): ORIGIN = FLASH_START, LENGTH = FLASH_SIZE
    OTP         (rx): ORIGIN = 0x03000C00, LENGTH = 1020
    RAM        (rwx): ORIGIN = 0x1FFF8000, LENGTH = 188K
    RET_RAM    (rwx): ORIGIN = 0x200F0000, LENGTH = 4K
}
```

all other memory regions are left untouched.

### 3. `.vector` and `.icg_sec` fixed size

the `.vector` and `.icg_sec` sections are defined with a fixed size of 1024 and 32 bytes respectively.
This is done by manually setting the program counter to the desired address after the section contents:

```cpp
SECTIONS
{
    /* 1024 bytes fixed size */
    .vectors :
    {
        KEEP(*(.vectors))
        . = 1024;
    } >FLASH


    /* 32 bytes fixed size */
    .icg_sec :
    {
        KEEP(*(.icg_sec))
        . = 1024 + 32;
    } >FLASH

    /* append all other FLASH sections after */
    .text :
    // ...
}
```

## `/cores/ddl/startup/startup_hc32f460.S`

the startup code needs adjustments to work correctly with libc. 


### 1. `__libc_init_array` call

to initialize libc, a call to `__libc_init_array` is added before calling `main`:

```assembly
    /* Call the clock system initialization function. */
    bl          SystemInit
    /* call __libc_init_array before calling main */
    bl          __libc_init_array
    /* Call the application's entry point. */
    bl          main
```

