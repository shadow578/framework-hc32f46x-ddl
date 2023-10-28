#pragma once
#include "hc32_common.h"
#include "ddl_config.h"
#if (DDL_USART_ENABLE == DDL_ON)

#include "hc32f460_usart.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief set UART mode baudrate
     *
     * @note
     * hook into internals of DDL USART_SetBaudrate() function,
     * reduces code size by ~500 bytes if only using UART mode
     */
    extern en_result_t SetUartBaudrate(M4_USART_TypeDef *USARTx, uint32_t u32Baudrate);

    /**
     * @brief set smard card mode baudrate
     *
     * @note
     * hook into internals of DDL USART_SetBaudrate() function,
     * reduces code size by ~500 bytes if only using smart card mode
     */
    extern en_result_t SetClkSyncBaudrate(M4_USART_TypeDef *USARTx, uint32_t u32Baudrate);

    /**
     * @brief set synchronous clock mode baudrate
     *
     * @note
     * hook into internals of DDL USART_SetBaudrate() function,
     * reduces code size by ~500 bytes if only using synchronous clock mode
     */
    extern en_result_t SetScBaudrate(M4_USART_TypeDef *USARTx, uint32_t u32Baudrate);

#ifdef __cplusplus
}
#endif
#endif