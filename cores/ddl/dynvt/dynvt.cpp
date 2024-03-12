#include "dynvt.h"
#include <algorithm>

#define CORE_ASSERT(x, msg, ...) \
    if (!(x))                    \
    {                            \
        printf(msg);             \
        ##__VA_ARGS__;           \
    }

volatile vector_table_t dynvt;

const irq_vector_t *no_handler = &__default_handler;

void dynvt_init()
{
    // copy current vector table to RAM
    vector_table_t *current_vt = (vector_table_t *)SCB->VTOR;
    std::copy(current_vt, current_vt + sizeof(vector_table_t), &dynvt);

    // relocate vector table to RAM
    // this is done with interrupts disabled
    __disable_irq();
    SCB->VTOR = (uint32_t)&dynvt;
    _DSB();
    __enable_irq();
}

int interrupt_register(const en_int_src_t source, func_ptr_t handler)
{
    CORE_ASSERT(handler, "handler is null", return -1);

    // get next free irq #n
    IRQn_Type irqn;
    CORE_ASSERT(_irqn_aa_get(irqn) == Ok, "no free irq handler", return -1);

    // register interrupt
    stc_irq_regi_conf_t conf = {
        .enIntSrc = source,
        .enIRQn = irqn,
        .pfnCallback = handler,
    };
    CORE_ASSERT(enIrqRegistration(&conf) == Ok, "interrupt registration failed", return -1);

    return static_cast<int>(irqn);
}

bool interrupt_resign(const int irqn)
{
    CORE_ASSERT(irqn >= 0 && irqn <= 127, "IRQn out of range", return false);

    enIrqResign(static_cast<IRQn_Type>(irqn));
    _irqn_aa_resign(static_cast<IRQn_Type>(irqn));
    return true;
}

//
// compat
//
en_result_t enIrqRegistration(const stc_irq_regi_conf_t *pstcIrqRegiConf)
{
    CORE_ASSERT(pstcIrqRegiConf->pfnCallback, "callback is null");
    CORE_ASSERT(pstcIrqRegiConf->enIRQn >= Int000_IRQn && pstcIrqRegiConf->enIRQn <= Int127_IRQn, "IRQn out of range", return ErrorInvalidParameter);

    // TODO: IRQ032~127 whether out of range (?)
    // if (((((pstcIrqRegiConf->enIntSrc / 32) * 6 + 32) > pstcIrqRegiConf->enIRQn) ||
    //     (((pstcIrqRegiConf->enIntSrc / 32) * 6 + 37) < pstcIrqRegiConf->enIRQn)) &&
    //    (pstcIrqRegiConf->enIRQn >= 32))
    //{
    //    enRet = ErrorInvalidParameter;
    //}
    // =
    // (
    //   (((pstcIrqRegiConf->enIntSrc / 32) * 6 + 32) > pstcIrqRegiConf->enIRQn)
    //   OR
    //   (((pstcIrqRegiConf->enIntSrc / 32) * 6 + 37) < pstcIrqRegiConf->enIRQn)
    // )
    // AND
    // (pstcIrqRegiConf->enIRQn >= 32)

    // get interrupt selection register
    stc_intc_sel_field_t *intSel = static_cast<stc_intc_sel_field_t *>(&M4_INTC->SEL0 + (4u * pstcIrqRegiConf->enIRQn));
    CORE_ASSERT(intSel->INTSEL == 0x1FFu, "interrupt already registered", return ErrorUninitialized);

    // set interrupt selection
    intSel->INTSEL = pstcIrqRegiConf->enIntSrc;

    // set interrupt handler pointer in vector table
    CORE_ASSERT(dynvt.irqs[pstcIrqRegiConf->enIRQn] == no_handler, "handler already registered", return ErrorUninitialized);
    dynvt.irqs[pstcIrqRegiConf->enIRQn] = pstcIrqRegiConf->pfnCallback;
    return Ok;
}

en_result_t enIrqResign(IRQn_Type enIRQn)
{
    CORE_ASSERT(enIRQn >= Int000_IRQn && enIRQn <= Int127_IRQn, "IRQn out of range", return ErrorInvalidParameter);

    // get interrupt selection register
    stc_intc_sel_field_t *intSel = static_cast<stc_intc_sel_field_t *>(&M4_INTC->SEL0 + (4u * enIRQn));
    CORE_ASSERT(intSel->INTSEL != 0x1FFu, "interrupt not registered" /*, return ErrorUninitialized*/);

    // reset interrupt selection
    intSel->INTSEL = 0x1FFu;

    // reset interrupt handler pointer in vector table
    CORE_ASSERT(dynvt.irqs[enIRQn] != no_handler, "handler not registered" /*, return ErrorUninitialized*/);
    dynvt.irqs[enIRQn] = no_handler;
    return Ok;
}

en_result_t _irqn_aa_get(IRQn_Type &irqn)
{
    // find next irq handler #n that is set to no_handler
    // 0 <= n <= 127
    for (int n = 0; n <= 127; n++)
    {
        if (dynvt.irqs[n] == no_handler)
        {
            irqn = static_cast<IRQn_Type>(n);
            return Ok;
        }
    }

    // no free irq handler found
    return Error;
}

en_result_t _irqn_aa_resign(IRQn_Type &irqn)
{
    // do nothing, irq resign is done in enIrqResign
    return Ok;
}