#include "startup.h"
#include <algorithm>
#include <hc32f460.h>

//
// reset handler implementation
//
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
    //static_assert(&__data_end__ >= &__data_start__, "data end must be greater than or equal to data start");
    size_t size = &__data_end__ - &__data_start__;
    std::copy(&__etext, &__etext + size, &__data_start__);

    // copy .retdata from ROM to RAM
    //static_assert(&__data_end_ret_ram__ >= &__data_start_ret_ram__, "retdata end must be greater than or equal to retdata start");
    size = &__data_end_ret_ram__ - &__data_start_ret_ram__;
    std::copy(&__etext_ret_ram, &__etext_ret_ram + size, &__data_start_ret_ram__);

    // clear .bss
    //static_assert(&__bss_end__ >= &__bss_start__, "bss end must be greater than or equal to bss start");
    size = &__bss_end__ - &__bss_start__;
    std::fill(&__bss_start__, &__bss_end__, 0);

    // clear .retbss
    //static_assert(&__bss_end_ret_ram__ >= &__bss_start_ret_ram__, "retbss end must be greater than or equal to retbss start");
    size = &__bss_end_ret_ram__ - &__bss_start_ret_ram__;
    std::fill(&__bss_start_ret_ram__, &__bss_end_ret_ram__, 0);

    // set SRAM3 wait states
    M4_SRAMC->WTPR = 0x77;
    M4_SRAMC->CKPR = 0x77;
    M4_SRAMC->WTCR = 0x1100;
    M4_SRAMC->WTPR = 0x76;
    M4_SRAMC->CKPR = 0x76;

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
