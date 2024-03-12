//
// compatibility header for dynvt to hc32460_interrupts ddl
//
#ifndef __DYNVT_INTERRUPTS_COMPAT_H__
#define __DYNVT_INTERRUPTS_COMPAT_H__
#include <hc32_ddl.h>

#define DDL_IRQ_PRIORITY_DEFAULT 15u
#define DDL_IRQ_PRIORITY_00 (0u)
#define DDL_IRQ_PRIORITY_01 (1u)
#define DDL_IRQ_PRIORITY_02 (2u)
#define DDL_IRQ_PRIORITY_03 (3u)
#define DDL_IRQ_PRIORITY_04 (4u)
#define DDL_IRQ_PRIORITY_05 (5u)
#define DDL_IRQ_PRIORITY_06 (6u)
#define DDL_IRQ_PRIORITY_07 (7u)
#define DDL_IRQ_PRIORITY_08 (8u)
#define DDL_IRQ_PRIORITY_09 (9u)
#define DDL_IRQ_PRIORITY_10 (10u)
#define DDL_IRQ_PRIORITY_11 (11u)
#define DDL_IRQ_PRIORITY_12 (12u)
#define DDL_IRQ_PRIORITY_13 (13u)
#define DDL_IRQ_PRIORITY_14 (14u)
#define DDL_IRQ_PRIORITY_15 (15u)

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct stc_irq_regi_conf
    {
        en_int_src_t enIntSrc;
        IRQn_Type enIRQn;
        func_ptr_t pfnCallback;
    } stc_irq_regi_conf_t;

    static inline void AOS_SW_Trigger(void)
    {
        bM4_AOS_INT_SFTTRG_STRG = 1u;
    }

    extern en_result_t enIrqRegistration(const stc_irq_regi_conf_t *pstcIrqRegiConf);
    extern en_result_t enIrqResign(IRQn_Type enIRQn);

#ifdef __cplusplus
}
#endif
#endif // __DYNVT_INTERRUPTS_COMPAT_H__
