#include "startup.h"
#include <algorithm>
#include <hc32f460.h>
#include "hc32f460_utility.h"

extern "C" __attribute__((naked, used, optimize("O0"))) void Reset_Handler(void)
{
    __asm__ __volatile__(
        // set stack pointer
        "ldr sp, =__StackTop\n"

        // branch to C++ reset handler
        "b Reset_Handler_C\n");
}

extern "C" void Reset_Handler_C(void)
{
    // copy .data from ROM to RAM
    DDL_ASSERT(&__data_end__ >= &__data_start__); // data end must be greater than or equal to data start
    size_t size = &__data_end__ - &__data_start__;
    std::copy(&__etext, &__etext + size, &__data_start__);

    // copy .retdata from ROM to RAM
    DDL_ASSERT(&__data_end_ret_ram__ >= &__data_start_ret_ram__); // retdata end must be greater than or equal to retdata start
    size = &__data_end_ret_ram__ - &__data_start_ret_ram__;
    std::copy(&__etext_ret_ram, &__etext_ret_ram + size, &__data_start_ret_ram__);

    // clear .bss
    DDL_ASSERT(&__bss_end__ >= &__bss_start__); // bss end must be greater than or equal to bss start
    size = &__bss_end__ - &__bss_start__;
    std::fill(&__bss_start__, &__bss_end__, 0);

    // clear .retbss
    DDL_ASSERT(&__bss_end_ret_ram__ >= &__bss_start_ret_ram__); // retbss end must be greater than or equal to retbss start
    size = &__bss_end_ret_ram__ - &__bss_start_ret_ram__;
    std::fill(&__bss_start_ret_ram__, &__bss_end_ret_ram__, 0);

    // set SRAM3 wait cycles
    M4_SRAMC->WTPR = 0x77; // unlock WTCR
    M4_SRAMC->CKPR = 0x77; // unlock 
    M4_SRAMC->WTCR_f = {
        .SRAM12_RWT = 0, // SRAM1 + SRAM2
        .SRAM12_WWT = 0, // SRAM1 + SRAM2
        .SRAM3_RWT  = 1, // SRAM3
        .SRAM3_WWT  = 1, // SRAM3
        .SRAMH_RWT  = 0, // SRAMH
        .SRAMH_WWT  = 0, // SRAMH
        .SRAMR_RWT  = 0, // RET_RAM
        .SRAMR_WWT  = 0, // RET_RAM
    };
    M4_SRAMC->WTPR = 0x76; // lock WTCR
    M4_SRAMC->CKPR = 0x76; // lock CKCR

    // init system and call main
    SystemInit();
    __libc_init_array();
    main();

    // call on_after_main, reset system
    __on_after_main();
    __NVIC_SystemReset();
}

__attribute__((weak)) void __on_after_main(void)
{
    // default handler just hangs
    while (true)
        ;
}

__attribute__((weak)) void __on_default_handler(void)
{
    // default handler just hangs
    while (true)
        ;
}
