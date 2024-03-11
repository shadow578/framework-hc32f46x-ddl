#ifndef __STARTUP_H__
#define __STARTUP_H__
#include <stdint.h>
#include "ld_symbols.h"
#include "interrupts.h"
#include "vector_table.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief DDL system initialization
     */
    extern void SystemInit(void);

    /**
     * @brief libc array init
     */
    extern void __libc_init_array(void);

    /**
     * @brief application entry point
     */
    extern int main(void);
#ifdef __cplusplus
}
#endif
#endif // __STARTUP_H__
