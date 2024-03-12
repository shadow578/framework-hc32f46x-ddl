//
// compatibility header for dynvt to irqn auto-assignment driver
//
#ifndef __DYNVT_IRQN_AA_COMPAT_H__
#define __DYNVT_IRQN_AA_COMPAT_H__
#include <hc32_ddl.h>
#include "../../core_debug.h"

#ifdef __cplusplus
extern "C"
{
#endif

    en_result_t _irqn_aa_get(IRQn_Type &irqn);
    en_result_t _irqn_aa_resign(IRQn_Type &irqn);

#ifdef __CORE_DEBUG

    /**
     * @brief get auto-assigned IRQn
     * @param irqn assigned IRQn
     * @param name name of the IRQn (for debug purposes)
     * @return Ok or Error
     */
    inline en_result_t irqn_aa_get(IRQn_Type &irqn, const char *name)
    {
        if (_irqn_aa_get(irqn) != Ok)
        {
            panic_begin();
            panic_printf("IRQn auto-assignment failed for %s", name);
            panic_end();
        }

        CORE_DEBUG_PRINTF("IRQ%d auto-assigned to %s\n", int(irqn), name);
        return Ok;
    }

    /**
     * @brief resign auto-assigned IRQn
     * @param irqn IRQn to resign
     * @param name name of the IRQn (for debug purposes)
     * @return Ok or Error
     */
    inline en_result_t irqn_aa_resign(IRQn_Type &irqn, const char *name)
    {
        if (_irqn_aa_resign(irqn) != Ok)
        {
            panic_begin();
            panic_printf("IRQn auto-resign failed for %s", name);
            panic_end();
        }

        CORE_DEBUG_PRINTF("%s auto-resigned IRQ%d\n", name, int(irqn));
        return Ok;
    }

#else
#define irqn_aa_get(irqn, name) _irqn_aa_get(irqn)
#define irqn_aa_resign(irqn, name) _irqn_aa_resign(irqn)
#endif

#ifdef __cplusplus
}
#endif
#endif // __DYNVT_IRQN_AA_COMPAT_H__
