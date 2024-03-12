#ifndef __DYNVT_H__
#define __DYNVT_H__
#include <startup/startup.h>
#include "ddl_interrupts_compat.h"
#include "irqn_aa_compat.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief dynamic vector table in RAM
     */
    volatile vector_table_t dynvt;

    /**
     * @brief initialize dynamic vector table
     */
    void dynvt_init(void);

    /**
     * @brief register interrupt handler for specified source
     * @param source interrupt source
     * @param handler interrupt handler
     * @return IRQn that was assigned. required for interrupt resign. -1 if failed
     * @note automatically assigns the handler to the next available IRQn
     */
    int interrupt_register(const en_int_src_t source, func_ptr_t handler);

    /**
     * @brief resign interrupt handler for specified IRQn
     * @param irqn IRQn to resign
     * @return true if successful, false if failed
     */
    bool interrupt_resign(const int irqn);

#ifdef __cplusplus
}
#endif
#endif // __DYNVT_H__
