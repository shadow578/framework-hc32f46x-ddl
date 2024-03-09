#include "startup.h"
#include <hc32f460.h>
#include <algorithm>

volatile char stack[DDL_STACK_SIZE] __attribute__((section(".stack"), aligned(8), used));
volatile char heap[DDL_HEAP_SIZE] __attribute__((section(".heap"), aligned(8), used));

//
// reset handler implementation
//
#define __ALWAYS_INLINE __attribute__((always_inline)) inline
#define __O0 __attribute__((optimize("O0")))

/**
 * @brief set SRAM3 wait states
 */
__O0 void setSRAM3Wait()
{
    M4_SRAMC->WTPR = 0x77;
    M4_SRAMC->CKPR = 0x77;
    M4_SRAMC->WTCR = 0x1100;
    M4_SRAMC->WTPR = 0x76;
    M4_SRAMC->CKPR = 0x76;
}


extern "C" __attribute__((naked, used)) __O0 void Reset_Handler(void)
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
    uint32_t size = &__data_end__ - &__data_start__;
    std::copy(&__etext, &__etext + size, &__data_start__);

    // copy .ret_ram_data from ROM to RAM
    size = &__data_end_ret_ram__ - &__data_start_ret_ram__;
    std::copy(&__etext_ret_ram, &__etext_ret_ram + size, &__data_start_ret_ram__);

    // clear .bss
    std::fill(&__bss_start__, &__bss_end__, 0);

    // clear .ret_ram_bss
    std::fill(&__bss_start_ret_ram__, &__bss_end_ret_ram__, 0);

    // set SRAM3 wait states
    setSRAM3Wait();

    // initialize system and call main
    SystemInit();
    __libc_init_array();
    main();

    // main should never return
    // if it does, hang here
    while (1)
        ;
}
