#include <stdint.h>
#include <hc32f460.h> // for SRAM

#warning "using new startup.cpp"

//
// stack
//

#ifndef DDL_STACK_SIZE
#define DDL_STACK_SIZE 0x00000400
#endif

/**
 * @brief stack definition
 */
__attribute__((section(".stack"))) uint8_t stack[DDL_STACK_SIZE];
const uint8_t *stackBase = stack;
const uint8_t *stackTop = stack + DDL_STACK_SIZE;

static_assert(sizeof(stack) == DDL_STACK_SIZE, "stack size does not match expected size");

//
// heap
//

#ifndef DDL_HEAP_SIZE
#define DDL_HEAP_SIZE 0x00000400
#endif

/**
 * @brief heap definition
 */
__attribute__((section(".heap"))) uint8_t heap[DDL_HEAP_SIZE];
const uint8_t *heapBase = heap;
const uint8_t *heapTop = heap + DDL_HEAP_SIZE;

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
}

//
// reset handler
//

#define __ALWAYS_INLINE __attribute__((always_inline)) inline

/**
 * @brief copy .data and .ret_ram_data sections to SRAM
 */
__ALWAYS_INLINE void copyData()
{
  // copy .data section to SRAM
  uint32_t *src = &__etext;
  uint32_t *dst = &__data_start__;
  uint32_t *end = &__data_end__;
  while (dst < end)
  {
    *dst++ = *src++;
  }

  // copy ret_ram .data section to SRAM
  src = &__etext_ret_ram;
  dst = &__data_start_ret_ram__;
  end = &__data_end_ret_ram__;
  while (dst < end)
  {
    *dst++ = *src++;
  }
}

/**
 * @brief clear .bss and .ret_ram_bss sections
 */
__ALWAYS_INLINE void clearBss()
{
  // clear .bss section
  uint32_t *dst = &__bss_start__;
  uint32_t *end = &__bss_end__;
  while (dst < end)
  {
    *dst++ = 0;
  }

  // clear ret_ram .bss section
  dst = &__bss_start_ret_ram__;
  end = &__bss_end_ret_ram__;
  while (dst < end)
  {
    *dst++ = 0;
  }
}

/**
 * @brief set SRAM3 wait states
 */
__ALWAYS_INLINE void setSram3WaitStates()
{
// TODO remove this
//#define SET_REG(reg, value) *(reinterpret_cast<volatile uint32_t *>(reg)) = (value)
//#define SRAM_WTCR 0x40050800 // SRAM wait control register
//#define SRAM_WTPR 0x40050804 // SRAM wait protection register
//#define SRAM_CKPR 0x4005080C // SRAM check protection register
//
//  SET_REG(SRAM_WTPR, 0x77);
//  SET_REG(SRAM_CKPR, 0x77);
//  SET_REG(SRAM_WTCR, 0x1100);
//  SET_REG(SRAM_WTPR, 0x76);
//  SET_REG(SRAM_CKPR, 0x76);

  M4_SRAMC->WTPR = 0x77;
  M4_SRAMC->CKPR = 0x77;
  M4_SRAMC->WTCR = 0x1100;
  M4_SRAMC->WTPR = 0x76;
  M4_SRAMC->CKPR = 0x76;
}

/**
 * @brief reset handler
 */
extern "C" __attribute__((naked, noreturn)) void Reset_Handler(void)
{
  // set stack top pointer
  __asm__ volatile("ldr sp, =stackTop");

  // copy .data and .ret_ram_data sections to SRAM
  copyData();

  // clear .bss and .ret_ram_bss sections
  clearBss();

  // set SRAM3 wait states
  setSram3WaitStates();

  // initialize libc and ddl
  __libc_init_array();
  SystemInit();

  // call main function
  main();
}

//
// default irq handlers, weak symbols
//
extern "C" void __default_handler(void)
{
  while (true)
    ;
}

#define IRQ_HANDLER_ATTR __attribute__((weak, alias("__default_handler")))

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
typedef struct __attribute__((aligned(2)))
{
  /**
   * @brief top of stack
   */
  uint32_t stackTop;

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

/**
 * @brief vector table definition
 */
extern "C" __attribute__((section(".vectors"))) const vector_table_t vectors = {
    .stackTop = reinterpret_cast<uint32_t>(stackTop),
    .reset = Reset_Handler,
    .nmi = NMI_Handler,
    .hardFault = HardFault_Handler,
    .memManageFault = MemManage_Handler,
    .busFault = BusFault_Handler,
    .usageFault = UsageFault_Handler,
    .svCall = SVC_Handler,
    .debugMonitor = DebugMon_Handler,
    .pendSV = PendSV_Handler,
    .sysTick = SysTick_Handler,

    .irqs = {
        IRQ000_Handler,
        IRQ001_Handler,
        IRQ002_Handler,
        IRQ003_Handler,
        IRQ004_Handler,
        IRQ005_Handler,
        IRQ006_Handler,
        IRQ007_Handler,
        IRQ008_Handler,
        IRQ009_Handler,
        IRQ010_Handler,
        IRQ011_Handler,
        IRQ012_Handler,
        IRQ013_Handler,
        IRQ014_Handler,
        IRQ015_Handler,
        IRQ016_Handler,
        IRQ017_Handler,
        IRQ018_Handler,
        IRQ019_Handler,
        IRQ020_Handler,
        IRQ021_Handler,
        IRQ022_Handler,
        IRQ023_Handler,
        IRQ024_Handler,
        IRQ025_Handler,
        IRQ026_Handler,
        IRQ027_Handler,
        IRQ028_Handler,
        IRQ029_Handler,
        IRQ030_Handler,
        IRQ031_Handler,
        IRQ032_Handler,
        IRQ033_Handler,
        IRQ034_Handler,
        IRQ035_Handler,
        IRQ036_Handler,
        IRQ037_Handler,
        IRQ038_Handler,
        IRQ039_Handler,
        IRQ040_Handler,
        IRQ041_Handler,
        IRQ042_Handler,
        IRQ043_Handler,
        IRQ044_Handler,
        IRQ045_Handler,
        IRQ046_Handler,
        IRQ047_Handler,
        IRQ048_Handler,
        IRQ049_Handler,
        IRQ050_Handler,
        IRQ051_Handler,
        IRQ052_Handler,
        IRQ053_Handler,
        IRQ054_Handler,
        IRQ055_Handler,
        IRQ056_Handler,
        IRQ057_Handler,
        IRQ058_Handler,
        IRQ059_Handler,
        IRQ060_Handler,
        IRQ061_Handler,
        IRQ062_Handler,
        IRQ063_Handler,
        IRQ064_Handler,
        IRQ065_Handler,
        IRQ066_Handler,
        IRQ067_Handler,
        IRQ068_Handler,
        IRQ069_Handler,
        IRQ070_Handler,
        IRQ071_Handler,
        IRQ072_Handler,
        IRQ073_Handler,
        IRQ074_Handler,
        IRQ075_Handler,
        IRQ076_Handler,
        IRQ077_Handler,
        IRQ078_Handler,
        IRQ079_Handler,
        IRQ080_Handler,
        IRQ081_Handler,
        IRQ082_Handler,
        IRQ083_Handler,
        IRQ084_Handler,
        IRQ085_Handler,
        IRQ086_Handler,
        IRQ087_Handler,
        IRQ088_Handler,
        IRQ089_Handler,
        IRQ090_Handler,
        IRQ091_Handler,
        IRQ092_Handler,
        IRQ093_Handler,
        IRQ094_Handler,
        IRQ095_Handler,
        IRQ096_Handler,
        IRQ097_Handler,
        IRQ098_Handler,
        IRQ099_Handler,
        IRQ100_Handler,
        IRQ101_Handler,
        IRQ102_Handler,
        IRQ103_Handler,
        IRQ104_Handler,
        IRQ105_Handler,
        IRQ106_Handler,
        IRQ107_Handler,
        IRQ108_Handler,
        IRQ109_Handler,
        IRQ110_Handler,
        IRQ111_Handler,
        IRQ112_Handler,
        IRQ113_Handler,
        IRQ114_Handler,
        IRQ115_Handler,
        IRQ116_Handler,
        IRQ117_Handler,
        IRQ118_Handler,
        IRQ119_Handler,
        IRQ120_Handler,
        IRQ121_Handler,
        IRQ122_Handler,
        IRQ123_Handler,
        IRQ124_Handler,
        IRQ125_Handler,
        IRQ126_Handler,
        IRQ127_Handler,
        IRQ128_Handler,
        IRQ129_Handler,
        IRQ130_Handler,
        IRQ131_Handler,
        IRQ132_Handler,
        IRQ133_Handler,
        IRQ134_Handler,
        IRQ135_Handler,
        IRQ136_Handler,
        IRQ137_Handler,
        IRQ138_Handler,
        IRQ139_Handler,
        IRQ140_Handler,
        IRQ141_Handler,
        IRQ142_Handler,
        IRQ143_Handler,
    },
};
