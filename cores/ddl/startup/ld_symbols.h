#ifndef __LD_SYMBOLS_H__
#define __LD_SYMBOLS_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief start of the .data section in FLASH
     * @note located right after the .text section
     */
    extern uint32_t __etext;

    /**
     * @brief start of the .data section in RAM
     */
    extern uint32_t __data_start__;

    /**
     * @brief end of the .data section in RAM
     */
    extern uint32_t __data_end__;

    /**
     * @brief start of the .ret_ram_data section in FLASH
     * @note located right after the .data section
     */
    extern uint32_t __etext_ret_ram;

    /**
     * @brief start of the .ret_ram_data section in RAM
     */
    extern uint32_t __data_start_ret_ram__;

    /**
     * @brief end of the .ret_ram_data section in RAM
     */
    extern uint32_t __data_end_ret_ram__;

    /**
     * @brief start of the .bss section in RAM
     */
    extern uint32_t __bss_start__;

    /**
     * @brief end of the .bss section in RAM
     */
    extern uint32_t __bss_end__;

    /**
     * @brief start of .ret_ram_bss in RAM
     */
    extern uint32_t __bss_start_ret_ram__;

    /**
     * @brief end of .ret_ram_bss in RAM
     */
    extern uint32_t __bss_end_ret_ram__;

    /**
     * @brief top of the stack
     */
    extern uint32_t __StackTop;
#ifdef __cplusplus
}
#endif
#endif // __LD_SYMBOLS_H__
