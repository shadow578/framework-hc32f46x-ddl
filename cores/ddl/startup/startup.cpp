#include <stdint.h>
#include <stdlib.h>
#include <hc32f460.h> // for SRAM

#warning "using new startup.cpp"

//
// extern symbols (by linker or other modules)
//
extern "C"
{
  /**
   * @brief libc init
   */
  extern void __libc_init_array(void);

  /**
   * @brief ddl init
   */
  extern void SystemInit(void);

  /**
   * @brief app main function
   */
  extern int main(void);

  /**
   * @brief end of .text section
   */
  extern uint32_t __etext;

  /**
   * @brief start of .data section
   */
  extern uint32_t __data_start__;

  /**
   * @brief end of .data section
   */
  extern uint32_t __data_end__;

  /**
   * @brief end of ret_ram .text section
   */
  extern uint32_t __etext_ret_ram;

  /**
   * @brief start of ret_ram .data section
   */
  extern uint32_t __data_start_ret_ram__;

  /**
   * @brief end of ret_ram .data section
   */
  extern uint32_t __data_end_ret_ram__;

  /**
   * @brief start of .bss section
   */
  extern uint32_t __bss_start__;

  /**
   * @brief end of .bss section
   */
  extern uint32_t __bss_end__;

  /**
   * @brief end of .ret_ram_bss section
   */
  extern uint32_t __bss_start_ret_ram__;

  /**
   * @brief end of .ret_ram_bss section
   */
  extern uint32_t __bss_end_ret_ram__;

  extern uint32_t __HeapLimit;
  extern uint32_t __StackLimit;
  extern uint32_t __StackTop;
}

//
// reset handler
//

#define __ALWAYS_INLINE __attribute__((always_inline)) inline

//
// default irq handlers, weak symbols
//
extern "C" void __default_handler(void)
{
  while (true)
    ;
}

#define IRQ_HANDLER_ATTR __attribute__((interrupt, weak, alias("__default_handler")))

extern "C" IRQ_HANDLER_ATTR void NMI_Handler(void);
extern "C" IRQ_HANDLER_ATTR void HardFault_Handler(void);
extern "C" IRQ_HANDLER_ATTR void MemManage_Handler(void);
extern "C" IRQ_HANDLER_ATTR void BusFault_Handler(void);
extern "C" IRQ_HANDLER_ATTR void UsageFault_Handler(void);
extern "C" IRQ_HANDLER_ATTR void SVC_Handler(void);
extern "C" IRQ_HANDLER_ATTR void DebugMon_Handler(void);
extern "C" IRQ_HANDLER_ATTR void PendSV_Handler(void);
extern "C" IRQ_HANDLER_ATTR void SysTick_Handler(void);

extern "C" IRQ_HANDLER_ATTR void IRQ000_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ001_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ002_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ003_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ004_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ005_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ006_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ007_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ008_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ009_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ010_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ011_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ012_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ013_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ014_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ015_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ016_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ017_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ018_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ019_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ020_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ021_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ022_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ023_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ024_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ025_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ026_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ027_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ028_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ029_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ030_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ031_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ032_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ033_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ034_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ035_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ036_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ037_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ038_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ039_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ040_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ041_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ042_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ043_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ044_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ045_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ046_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ047_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ048_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ049_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ050_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ051_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ052_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ053_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ054_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ055_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ056_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ057_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ058_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ059_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ060_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ061_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ062_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ063_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ064_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ065_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ066_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ067_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ068_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ069_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ070_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ071_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ072_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ073_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ074_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ075_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ076_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ077_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ078_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ079_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ080_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ081_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ082_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ083_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ084_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ085_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ086_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ087_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ088_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ089_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ090_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ091_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ092_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ093_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ094_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ095_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ096_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ097_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ098_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ099_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ100_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ101_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ102_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ103_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ104_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ105_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ106_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ107_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ108_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ109_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ110_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ111_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ112_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ113_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ114_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ115_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ116_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ117_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ118_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ119_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ120_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ121_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ122_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ123_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ124_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ125_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ126_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ127_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ128_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ129_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ130_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ131_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ132_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ133_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ134_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ135_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ136_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ137_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ138_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ139_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ140_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ141_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ142_Handler(void);
extern "C" IRQ_HANDLER_ATTR void IRQ143_Handler(void);

//
// vector table
//

/**
 * @brief IRQ handler pointer
 */
typedef void (*irq_vector_t)(void);

/**
 * @brief vector table definition of HC32F460
 */
typedef struct __attribute__((packed))
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

/**
 * @brief check the size of irq_vector_t and uint32_t match the expectations
 */
static_assert(sizeof(irq_vector_t) == 4, "irq_vector_t must be 4 bytes");
static_assert(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
static_assert(sizeof(vector_table_t) == (16 + 144) * 4, "vector_table_t does not match expected size");

extern "C" void Reset_Handler(void);

/**
 * @brief vector table definition
 */
__attribute__((section(".vectors"))) const volatile uintptr_t vectors[] = {
    reinterpret_cast<uintptr_t>(&__StackTop),
    reinterpret_cast<uintptr_t>(Reset_Handler),
    reinterpret_cast<uintptr_t>(NMI_Handler),
    reinterpret_cast<uintptr_t>(HardFault_Handler),
    reinterpret_cast<uintptr_t>(MemManage_Handler),
    reinterpret_cast<uintptr_t>(BusFault_Handler),
    reinterpret_cast<uintptr_t>(UsageFault_Handler),

    reinterpret_cast<uintptr_t>(nullptr),
    reinterpret_cast<uintptr_t>(nullptr),
    reinterpret_cast<uintptr_t>(nullptr),
    reinterpret_cast<uintptr_t>(nullptr),

    reinterpret_cast<uintptr_t>(SVC_Handler),
    reinterpret_cast<uintptr_t>(DebugMon_Handler),

    reinterpret_cast<uintptr_t>(nullptr),

    reinterpret_cast<uintptr_t>(PendSV_Handler),
    reinterpret_cast<uintptr_t>(SysTick_Handler),

    reinterpret_cast<uintptr_t>(IRQ000_Handler),
    reinterpret_cast<uintptr_t>(IRQ001_Handler),
    reinterpret_cast<uintptr_t>(IRQ002_Handler),
    reinterpret_cast<uintptr_t>(IRQ003_Handler),
    reinterpret_cast<uintptr_t>(IRQ004_Handler),
    reinterpret_cast<uintptr_t>(IRQ005_Handler),
    reinterpret_cast<uintptr_t>(IRQ006_Handler),
    reinterpret_cast<uintptr_t>(IRQ007_Handler),
    reinterpret_cast<uintptr_t>(IRQ008_Handler),
    reinterpret_cast<uintptr_t>(IRQ009_Handler),
    reinterpret_cast<uintptr_t>(IRQ010_Handler),
    reinterpret_cast<uintptr_t>(IRQ011_Handler),
    reinterpret_cast<uintptr_t>(IRQ012_Handler),
    reinterpret_cast<uintptr_t>(IRQ013_Handler),
    reinterpret_cast<uintptr_t>(IRQ014_Handler),
    reinterpret_cast<uintptr_t>(IRQ015_Handler),
    reinterpret_cast<uintptr_t>(IRQ016_Handler),
    reinterpret_cast<uintptr_t>(IRQ017_Handler),
    reinterpret_cast<uintptr_t>(IRQ018_Handler),
    reinterpret_cast<uintptr_t>(IRQ019_Handler),
    reinterpret_cast<uintptr_t>(IRQ020_Handler),
    reinterpret_cast<uintptr_t>(IRQ021_Handler),
    reinterpret_cast<uintptr_t>(IRQ022_Handler),
    reinterpret_cast<uintptr_t>(IRQ023_Handler),
    reinterpret_cast<uintptr_t>(IRQ024_Handler),
    reinterpret_cast<uintptr_t>(IRQ025_Handler),
    reinterpret_cast<uintptr_t>(IRQ026_Handler),
    reinterpret_cast<uintptr_t>(IRQ027_Handler),
    reinterpret_cast<uintptr_t>(IRQ028_Handler),
    reinterpret_cast<uintptr_t>(IRQ029_Handler),
    reinterpret_cast<uintptr_t>(IRQ030_Handler),
    reinterpret_cast<uintptr_t>(IRQ031_Handler),
    reinterpret_cast<uintptr_t>(IRQ032_Handler),
    reinterpret_cast<uintptr_t>(IRQ033_Handler),
    reinterpret_cast<uintptr_t>(IRQ034_Handler),
    reinterpret_cast<uintptr_t>(IRQ035_Handler),
    reinterpret_cast<uintptr_t>(IRQ036_Handler),
    reinterpret_cast<uintptr_t>(IRQ037_Handler),
    reinterpret_cast<uintptr_t>(IRQ038_Handler),
    reinterpret_cast<uintptr_t>(IRQ039_Handler),
    reinterpret_cast<uintptr_t>(IRQ040_Handler),
    reinterpret_cast<uintptr_t>(IRQ041_Handler),
    reinterpret_cast<uintptr_t>(IRQ042_Handler),
    reinterpret_cast<uintptr_t>(IRQ043_Handler),
    reinterpret_cast<uintptr_t>(IRQ044_Handler),
    reinterpret_cast<uintptr_t>(IRQ045_Handler),
    reinterpret_cast<uintptr_t>(IRQ046_Handler),
    reinterpret_cast<uintptr_t>(IRQ047_Handler),
    reinterpret_cast<uintptr_t>(IRQ048_Handler),
    reinterpret_cast<uintptr_t>(IRQ049_Handler),
    reinterpret_cast<uintptr_t>(IRQ050_Handler),
    reinterpret_cast<uintptr_t>(IRQ051_Handler),
    reinterpret_cast<uintptr_t>(IRQ052_Handler),
    reinterpret_cast<uintptr_t>(IRQ053_Handler),
    reinterpret_cast<uintptr_t>(IRQ054_Handler),
    reinterpret_cast<uintptr_t>(IRQ055_Handler),
    reinterpret_cast<uintptr_t>(IRQ056_Handler),
    reinterpret_cast<uintptr_t>(IRQ057_Handler),
    reinterpret_cast<uintptr_t>(IRQ058_Handler),
    reinterpret_cast<uintptr_t>(IRQ059_Handler),
    reinterpret_cast<uintptr_t>(IRQ060_Handler),
    reinterpret_cast<uintptr_t>(IRQ061_Handler),
    reinterpret_cast<uintptr_t>(IRQ062_Handler),
    reinterpret_cast<uintptr_t>(IRQ063_Handler),
    reinterpret_cast<uintptr_t>(IRQ064_Handler),
    reinterpret_cast<uintptr_t>(IRQ065_Handler),
    reinterpret_cast<uintptr_t>(IRQ066_Handler),
    reinterpret_cast<uintptr_t>(IRQ067_Handler),
    reinterpret_cast<uintptr_t>(IRQ068_Handler),
    reinterpret_cast<uintptr_t>(IRQ069_Handler),
    reinterpret_cast<uintptr_t>(IRQ070_Handler),
    reinterpret_cast<uintptr_t>(IRQ071_Handler),
    reinterpret_cast<uintptr_t>(IRQ072_Handler),
    reinterpret_cast<uintptr_t>(IRQ073_Handler),
    reinterpret_cast<uintptr_t>(IRQ074_Handler),
    reinterpret_cast<uintptr_t>(IRQ075_Handler),
    reinterpret_cast<uintptr_t>(IRQ076_Handler),
    reinterpret_cast<uintptr_t>(IRQ077_Handler),
    reinterpret_cast<uintptr_t>(IRQ078_Handler),
    reinterpret_cast<uintptr_t>(IRQ079_Handler),
    reinterpret_cast<uintptr_t>(IRQ080_Handler),
    reinterpret_cast<uintptr_t>(IRQ081_Handler),
    reinterpret_cast<uintptr_t>(IRQ082_Handler),
    reinterpret_cast<uintptr_t>(IRQ083_Handler),
    reinterpret_cast<uintptr_t>(IRQ084_Handler),
    reinterpret_cast<uintptr_t>(IRQ085_Handler),
    reinterpret_cast<uintptr_t>(IRQ086_Handler),
    reinterpret_cast<uintptr_t>(IRQ087_Handler),
    reinterpret_cast<uintptr_t>(IRQ088_Handler),
    reinterpret_cast<uintptr_t>(IRQ089_Handler),
    reinterpret_cast<uintptr_t>(IRQ090_Handler),
    reinterpret_cast<uintptr_t>(IRQ091_Handler),
    reinterpret_cast<uintptr_t>(IRQ092_Handler),
    reinterpret_cast<uintptr_t>(IRQ093_Handler),
    reinterpret_cast<uintptr_t>(IRQ094_Handler),
    reinterpret_cast<uintptr_t>(IRQ095_Handler),
    reinterpret_cast<uintptr_t>(IRQ096_Handler),
    reinterpret_cast<uintptr_t>(IRQ097_Handler),
    reinterpret_cast<uintptr_t>(IRQ098_Handler),
    reinterpret_cast<uintptr_t>(IRQ099_Handler),
    reinterpret_cast<uintptr_t>(IRQ100_Handler),
    reinterpret_cast<uintptr_t>(IRQ101_Handler),
    reinterpret_cast<uintptr_t>(IRQ102_Handler),
    reinterpret_cast<uintptr_t>(IRQ103_Handler),
    reinterpret_cast<uintptr_t>(IRQ104_Handler),
    reinterpret_cast<uintptr_t>(IRQ105_Handler),
    reinterpret_cast<uintptr_t>(IRQ106_Handler),
    reinterpret_cast<uintptr_t>(IRQ107_Handler),
    reinterpret_cast<uintptr_t>(IRQ108_Handler),
    reinterpret_cast<uintptr_t>(IRQ109_Handler),
    reinterpret_cast<uintptr_t>(IRQ110_Handler),
    reinterpret_cast<uintptr_t>(IRQ111_Handler),
    reinterpret_cast<uintptr_t>(IRQ112_Handler),
    reinterpret_cast<uintptr_t>(IRQ113_Handler),
    reinterpret_cast<uintptr_t>(IRQ114_Handler),
    reinterpret_cast<uintptr_t>(IRQ115_Handler),
    reinterpret_cast<uintptr_t>(IRQ116_Handler),
    reinterpret_cast<uintptr_t>(IRQ117_Handler),
    reinterpret_cast<uintptr_t>(IRQ118_Handler),
    reinterpret_cast<uintptr_t>(IRQ119_Handler),
    reinterpret_cast<uintptr_t>(IRQ120_Handler),
    reinterpret_cast<uintptr_t>(IRQ121_Handler),
    reinterpret_cast<uintptr_t>(IRQ122_Handler),
    reinterpret_cast<uintptr_t>(IRQ123_Handler),
    reinterpret_cast<uintptr_t>(IRQ124_Handler),
    reinterpret_cast<uintptr_t>(IRQ125_Handler),
    reinterpret_cast<uintptr_t>(IRQ126_Handler),
    reinterpret_cast<uintptr_t>(IRQ127_Handler),
    reinterpret_cast<uintptr_t>(IRQ128_Handler),
    reinterpret_cast<uintptr_t>(IRQ129_Handler),
    reinterpret_cast<uintptr_t>(IRQ130_Handler),
    reinterpret_cast<uintptr_t>(IRQ131_Handler),
    reinterpret_cast<uintptr_t>(IRQ132_Handler),
    reinterpret_cast<uintptr_t>(IRQ133_Handler),
    reinterpret_cast<uintptr_t>(IRQ134_Handler),
    reinterpret_cast<uintptr_t>(IRQ135_Handler),
    reinterpret_cast<uintptr_t>(IRQ136_Handler),
    reinterpret_cast<uintptr_t>(IRQ137_Handler),
    reinterpret_cast<uintptr_t>(IRQ138_Handler),
    reinterpret_cast<uintptr_t>(IRQ139_Handler),
    reinterpret_cast<uintptr_t>(IRQ140_Handler),
    reinterpret_cast<uintptr_t>(IRQ141_Handler),
    reinterpret_cast<uintptr_t>(IRQ142_Handler),
    reinterpret_cast<uintptr_t>(IRQ143_Handler),
};
