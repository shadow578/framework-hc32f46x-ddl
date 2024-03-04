/**
 * simple example showcasing how to use the usart peripheral by polling.
 * this example will echo back any data received on the usart, byte by byte.
 * 
 * note that this is a very simple example. when using the usart in a real application,
 * you should consider using interrupts or dma to handle the data transfer. 
 */

#include <hc32_ddl.h>

// usart peripheral
#define USART M4_USART1
#define USART_CLK PWC_FCG1_PERIPH_USART1
#define USART_RX_FUNC Func_Usart1_Rx
#define USART_TX_FUNC Func_Usart1_Tx

// RX on PB08
#define RX_PORT PortB
#define RX_PIN Pin08

// TX on PB09
#define TX_PORT PortB
#define TX_PIN Pin09

void init_usart()
{
  // enable usart peripheral clock
  PWC_Fcg1PeriphClockCmd(USART_CLK, Enable);

  // set rx and tx pin function
  PORT_SetFunc(RX_PORT, RX_PIN, USART_RX_FUNC, Disable);
  PORT_SetFunc(TX_PORT, TX_PIN, USART_TX_FUNC, Disable);

  // initialize usart peripheral
  stc_usart_uart_init_t config = {
    .enClkMode = UsartIntClkCkNoOutput,
    .enClkDiv = UsartClkDiv_1,
    .enDataLength = UsartDataBits8,
    .enDirection = UsartDataLsbFirst,
    .enStopBit = UsartOneStopBit,
    .enParity = UsartParityNone,
    .enSampleMode = UsartSampleBit8,
    .enDetectMode = UsartStartBitFallEdge,
    .enHwFlow = UsartRtsEnable,
  };
  USART_UART_Init(USART, &config);

  // set baudrate
  USART_SetBaudrate(USART, 115200);

  // enable RX and TX function
  USART_FuncCmd(USART, UsartRx, Enable);
  USART_FuncCmd(USART, UsartTx, Enable);
}

uint8_t usart_rx_one_byte()
{
  while(USART_GetStatus(USART, UsartRxNoEmpty) != Set)
  {
    // wait for data
  }

  // got data, return it
  return USART_RecData(USART);
}

void usart_tx_one_byte(uint8_t data)
{
  while(USART_GetStatus(USART, UsartTxEmpty) != Set)
  {
    // wait for tx buffer to be empty
  }

  // send data
  USART_SendData(USART, data);
}

int main()
{
  // update VTOR (only needed when using bootloader)
  SCB->VTOR = (((uint32_t)LD_FLASH_START) & SCB_VTOR_TBLOFF_Msk);

  // initialize usart
  init_usart();

  while(true)
  {
    // read data from usart, one byte at a time
    uint8_t data = usart_rx_one_byte();

    // echo data back, one byte at a time
    usart_tx_one_byte(data);
  }
}
