/**
 * simple blink example showcasing how to use the DDL and GPIO library.
 * 
 * The example toggles the LED attached to PA01 every 500ms.
 */

#include <hc32_ddl.h>

// led attached to PA01
#define LED_PORT PortA
#define LED_PIN Pin01

int main()
{
  // update VTOR (only needed when using bootloader)
  SCB->VTOR = (((uint32_t)LD_FLASH_START) & SCB_VTOR_TBLOFF_Msk);

  // set led pin to output mode
  stc_port_init_t ledPinInit = {
    .enPinMode = Pin_Mode_Out,
    .enExInt = Disable,
    .enPullUp = Disable,
  };
  PORT_Init(LED_PORT, LED_PIN, &ledPinInit);

  while(true)
  {
    // toggle led
    PORT_Toggle(LED_PORT, LED_PIN);
    
    // wait 500ms
    Ddl_Delay1ms(500);
  }
}
