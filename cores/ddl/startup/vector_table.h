#ifndef __VECTOR_TABLE_H__
#define __VECTOR_TABLE_H__
#include <stdint.h>

#define VECTOR_TABLE_IRQ_COUNT 144

#ifdef __cplusplus
extern "C"
{
#endif
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
        irq_vector_t irqs[VECTOR_TABLE_IRQ_COUNT];
    } vector_table_t;

    /**
     * @brief vector table
     */
    extern vector_table_t vector_table;
#ifdef __cplusplus
}
#endif
#endif // __VECTOR_TABLE_H__
