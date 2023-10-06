#pragma once
#include "hc32_common.h"
#include "ddl_config.h"
#if (DDL_GPIO_ENABLE == DDL_ON)

#include "hc32f460_gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief inverse of PORT_Init
    */
    en_result_t PORT_GetConfig(en_port_t port, uint16_t pin, stc_port_init_t *portConf);

    /**
     * @brief inverse of PORT_SetFunc
    */
    en_result_t PORT_GetFunc(en_port_t port, uint16_t pin, en_port_func_t *funcSel, en_functional_state_t *subFuncEn);

#ifdef __cplusplus
}
#endif
#endif
