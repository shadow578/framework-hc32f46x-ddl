#pragma GCC optimize ("O0")

#include <stdint.h>
#include <stdlib.h>
#include <hc32f460.h> // for SRAM

#warning "using new startup.cpp"

//
// extern symbols (by linker or other modules)
//
extern "C"
{
  /**
   * @brief libc init
   */
  extern void __libc_init_array(void);

  /**
   * @brief ddl init
   */
  extern void SystemInit(void);

  /**
   * @brief app main function
   */
  extern int main(void);

  /**
   * @brief end of .text section
   */
  extern uint32_t __etext;

  /**
   * @brief start of .data section
   */
  extern uint32_t __data_start__;

  /**
   * @brief end of .data section
   */
  extern uint32_t __data_end__;

  /**
   * @brief end of ret_ram .text section
   */
  extern uint32_t __etext_ret_ram;

  /**
   * @brief start of ret_ram .data section
   */
  extern uint32_t __data_start_ret_ram__;

  /**
   * @brief end of ret_ram .data section
   */
  extern uint32_t __data_end_ret_ram__;

  /**
   * @brief start of .bss section
   */
  extern uint32_t __bss_start__;

  /**
   * @brief end of .bss section
   */
  extern uint32_t __bss_end__;

  /**
   * @brief end of .ret_ram_bss section
   */
  extern uint32_t __bss_start_ret_ram__;

  /**
   * @brief end of .ret_ram_bss section
   */
  extern uint32_t __bss_end_ret_ram__;

  extern uint32_t __HeapLimit;
  extern uint32_t __StackLimit;
  extern uint32_t __StackTop;
}

//
// reset handler
//

#define __ALWAYS_INLINE __attribute__((always_inline)) inline

/**
 * @brief copy .data and .ret_ram_data sections to SRAM
 */
__ALWAYS_INLINE void copyData()
{
  // copy .data section to SRAM
  uint32_t *src = &__etext;
  uint32_t *dst = &__data_start__;
  uint32_t *end = &__data_end__;
  while (dst < end)
  {
    *dst++ = *src++;
  }

  // copy ret_ram .data section to SRAM
  src = &__etext_ret_ram;
  dst = &__data_start_ret_ram__;
  end = &__data_end_ret_ram__;
  while (dst < end)
  {
    *dst++ = *src++;
  }
}

/**
 * @brief clear .bss and .ret_ram_bss sections
 */
__ALWAYS_INLINE void clearBss()
{
  // clear .bss section
  uint32_t *dst = &__bss_start__;
  uint32_t *end = &__bss_end__;
  while (dst < end)
  {
    *dst++ = 0;
  }

  // clear ret_ram .bss section
  dst = &__bss_start_ret_ram__;
  end = &__bss_end_ret_ram__;
  while (dst < end)
  {
    *dst++ = 0;
  }
}

/**
 * @brief set SRAM3 wait states
 */
__ALWAYS_INLINE void setSram3WaitStates()
{
  // TODO remove this
  // #define SET_REG(reg, value) *(reinterpret_cast<volatile uint32_t *>(reg)) = (value)
  // #define SRAM_WTCR 0x40050800 // SRAM wait control register
  // #define SRAM_WTPR 0x40050804 // SRAM wait protection register
  // #define SRAM_CKPR 0x4005080C // SRAM check protection register
  //
  //  SET_REG(SRAM_WTPR, 0x77);
  //  SET_REG(SRAM_CKPR, 0x77);
  //  SET_REG(SRAM_WTCR, 0x1100);
  //  SET_REG(SRAM_WTPR, 0x76);
  //  SET_REG(SRAM_CKPR, 0x76);

  M4_SRAMC->WTPR = 0x77;
  M4_SRAMC->CKPR = 0x77;
  M4_SRAMC->WTCR = 0x1100;
  M4_SRAMC->WTPR = 0x76;
  M4_SRAMC->CKPR = 0x76;
}

/**
 * @brief system reset handler
 */
extern "C" __attribute__((interrupt)) void Reset_Handler(void)
{
  __asm__ volatile(
      // set stack pointer
      // required in case we boot from a bootloader
      "ldr sp, =__StackTop\n"

      // branch to the reset handler written in C
      "b Reset_Handler_C\n");
}

/** 
 * @brief reset handler in C
 */
extern "C" __attribute__((noreturn)) void Reset_Handler_C(void)
{
  // copy .data and .ret_ram_data sections to SRAM
  copyData();

  // clear .bss and .ret_ram_bss sections
  clearBss();

  // set SRAM3 wait states
  setSram3WaitStates();

  // initialize libc and ddl
  SystemInit();
  __libc_init_array();

  // call main function
  main();

  // we should NEVER EVER get here!
  // if we do, let's reset the MCU
  __NVIC_SystemReset();
}
