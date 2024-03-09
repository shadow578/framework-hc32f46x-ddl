#include <stdint.h>
#include <hc32f460.h>

#define __ALWAYS_INLINE __attribute__((always_inline)) inline
#define __O0 __attribute__((optimize("O0")))


extern "C" __attribute__((naked, used)) __O0 void Reset_Handler(void)
{
    __asm__ __volatile__(
        // set stack pointer
        "ldr sp, =__StackTop\n"

        // branch to C++ reset handler
        "b Reset_Handler_C\n");
}

__ALWAYS_INLINE __O0 void initDataSection()
{
    // start of .data in ROM (= immediately following .text)
    extern uint32_t __etext;

    // start of .data in RAM
    extern uint32_t __data_start__;

    // end of .data in RAM
    extern uint32_t __data_end__;

    // copy .data from ROM to RAM
    register uint32_t *src = &__etext;
    register uint32_t *dst = &__data_start__;
    register uint32_t *end = &__data_end__;
    for (; dst < end; dst++, src++)
    {
        *dst = *src;
    }
}

__ALWAYS_INLINE __O0 void initRetDataSection()
{
    // start of .ret_ram in ROM
    extern uint32_t __etext_ret_ram;

    // end of .retdata in ROM
    extern uint32_t __data_start_ret_ram__;

    // start of .retdata in RAM
    extern uint32_t __data_end_ret_ram__;

    // copy .retdata from ROM to RAM
    register uint32_t *src = &__etext_ret_ram;
    register uint32_t *dst = &__data_start_ret_ram__;
    register uint32_t *end = &__data_end_ret_ram__;
    for (; dst < end; src++, dst++)
    {
        *dst = *src;
    }
}

__ALWAYS_INLINE __O0 void initBssSection()
{
    // start of .bss in RAM
    extern uint32_t __bss_start__;

    // end of .bss in RAM
    extern uint32_t __bss_end__;

    // clear .bss
    register uint32_t *dst = &__bss_start__;
    register uint32_t *end = &__bss_end__;
    for (; dst < end; dst++)
    {
        *dst = 0;
    }
}

__ALWAYS_INLINE __O0 void initRetBssSection()
{
    // start of .retbss in RAM
    extern uint32_t __bss_start_ret_ram__;

    // end of .retbss in RAM
    extern uint32_t __bss_end_ret_ram__;

    // clear .retbss
    register uint32_t *dst = &__bss_start_ret_ram__;
    register uint32_t *end = &__bss_end_ret_ram__;
    for (; dst < end; dst++)
    {
        *dst = 0;
    }
}

__ALWAYS_INLINE __O0 void setSRAM3Wait()
{
    M4_SRAMC->WTPR = 0x77;
    M4_SRAMC->CKPR = 0x77;
    M4_SRAMC->WTCR = 0x1100;
    M4_SRAMC->WTPR = 0x76;
    M4_SRAMC->CKPR = 0x76;
}

extern "C" void SystemInit(void);
extern "C" void __libc_init_array(void);
extern "C" int main(void);

extern "C" __O0 void Reset_Handler_C(void)
{
    initDataSection();
    initRetDataSection();

    initBssSection();
    initRetBssSection();

    setSRAM3Wait();

    SystemInit();
    __libc_init_array();
    main();

    while (1)
        ;
}
