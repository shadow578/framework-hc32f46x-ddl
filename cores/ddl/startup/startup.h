#ifndef __STARTUP_H__
#define __STARTUP_H__
#include <stdint.h>
#include "ld_symbols.h"
#include "interrupts.h"

#ifndef DDL_STACK_SIZE
#define DDL_STACK_SIZE 0x00000400 // 1KB
#endif

#ifndef DDL_HEAP_SIZE
#define DDL_HEAP_SIZE 0x00002000 // 8KB
#endif

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

    /**
     * @brief stack memory
     */
    extern volatile char stack[];

    /**
     * @brief heap memory
     */
    extern volatile char heap[];

    /**
     * @brief IRQ handler pointer
     */
    typedef void (*irq_vector_t)(void);

    /**
     * @brief vector table definition of HC32F460
     */
    typedef struct
    {
        /**
         * @brief top of stack
         */
        uint32_t *stackTop;

        /**
         * @brief reset handler
         */
        irq_vector_t reset;

        /**
         * @brief NMI handler
         */
        irq_vector_t nmi;

        /**
         * @brief hard fault handler
         */
        irq_vector_t hardFault;

        /**
         * @brief MPU fault handler
         */
        irq_vector_t memManageFault;

        /**
         * @brief bus fault handler
         */
        irq_vector_t busFault;

        /**
         * @brief usage fault handler
         */
        irq_vector_t usageFault;

        /**
         * @brief reserved, 4 x 32bit
         */
        uint32_t reserved1[4];

        /**
         * @brief SVCall handler
         */
        irq_vector_t svCall;

        /**
         * @brief debug monitor handler
         */
        irq_vector_t debugMonitor;

        /**
         * @brief reserved, 1 x 32bit
         */
        uint32_t reserved2;

        /**
         * @brief PendSV handler
         */
        irq_vector_t pendSV;

        /**
         * @brief SysTick handler
         */
        irq_vector_t sysTick;

        /**
         * @brief IRQ handlers, total 144 vectors
         */
        irq_vector_t irqs[144];
    } vector_table_t;

#ifdef __cplusplus
}
#endif
#endif // __STARTUP_H__
