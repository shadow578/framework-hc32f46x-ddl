#include <stdint.h>

/**
 * @brief IRQ handler pointer
 */
typedef void (*irq_vector_t)(void);

/**
 * @brief vector table definition of HC32F460
 */
typedef struct
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

extern "C"
{
    extern uint32_t __StackTop;

    // interrupt handlers
    extern void Reset_Handler(void);      /*     Reset Handler */
    extern void NMI_Handler(void);        /* -14 NMI Handler */
    extern void HardFault_Handler(void);  /* -13 Hard Fault Handler */
    extern void MemManage_Handler(void);  /* -12 MPU Fault Handler */
    extern void BusFault_Handler(void);   /* -11 Bus Fault Handler */
    extern void UsageFault_Handler(void); /* -10 Usage Fault Handler */
    extern void SVC_Handler(void);        /*  -5 SVCall Handler */
    extern void DebugMon_Handler(void);   /*  -4 Debug Monitor Handler */
    extern void PendSV_Handler(void);     /*  -2 PendSV Handler */
    extern void SysTick_Handler(void);    /*  -1 SysTick Handler */

    /* Interrupts */
    extern void IRQ000_Handler(void);
    extern void IRQ001_Handler(void);
    extern void IRQ002_Handler(void);
    extern void IRQ003_Handler(void);
    extern void IRQ004_Handler(void);
    extern void IRQ005_Handler(void);
    extern void IRQ006_Handler(void);
    extern void IRQ007_Handler(void);
    extern void IRQ008_Handler(void);
    extern void IRQ009_Handler(void);
    extern void IRQ010_Handler(void);
    extern void IRQ011_Handler(void);
    extern void IRQ012_Handler(void);
    extern void IRQ013_Handler(void);
    extern void IRQ014_Handler(void);
    extern void IRQ015_Handler(void);
    extern void IRQ016_Handler(void);
    extern void IRQ017_Handler(void);
    extern void IRQ018_Handler(void);
    extern void IRQ019_Handler(void);
    extern void IRQ020_Handler(void);
    extern void IRQ021_Handler(void);
    extern void IRQ022_Handler(void);
    extern void IRQ023_Handler(void);
    extern void IRQ024_Handler(void);
    extern void IRQ025_Handler(void);
    extern void IRQ026_Handler(void);
    extern void IRQ027_Handler(void);
    extern void IRQ028_Handler(void);
    extern void IRQ029_Handler(void);
    extern void IRQ030_Handler(void);
    extern void IRQ031_Handler(void);
    extern void IRQ032_Handler(void);
    extern void IRQ033_Handler(void);
    extern void IRQ034_Handler(void);
    extern void IRQ035_Handler(void);
    extern void IRQ036_Handler(void);
    extern void IRQ037_Handler(void);
    extern void IRQ038_Handler(void);
    extern void IRQ039_Handler(void);
    extern void IRQ040_Handler(void);
    extern void IRQ041_Handler(void);
    extern void IRQ042_Handler(void);
    extern void IRQ043_Handler(void);
    extern void IRQ044_Handler(void);
    extern void IRQ045_Handler(void);
    extern void IRQ046_Handler(void);
    extern void IRQ047_Handler(void);
    extern void IRQ048_Handler(void);
    extern void IRQ049_Handler(void);
    extern void IRQ050_Handler(void);
    extern void IRQ051_Handler(void);
    extern void IRQ052_Handler(void);
    extern void IRQ053_Handler(void);
    extern void IRQ054_Handler(void);
    extern void IRQ055_Handler(void);
    extern void IRQ056_Handler(void);
    extern void IRQ057_Handler(void);
    extern void IRQ058_Handler(void);
    extern void IRQ059_Handler(void);
    extern void IRQ060_Handler(void);
    extern void IRQ061_Handler(void);
    extern void IRQ062_Handler(void);
    extern void IRQ063_Handler(void);
    extern void IRQ064_Handler(void);
    extern void IRQ065_Handler(void);
    extern void IRQ066_Handler(void);
    extern void IRQ067_Handler(void);
    extern void IRQ068_Handler(void);
    extern void IRQ069_Handler(void);
    extern void IRQ070_Handler(void);
    extern void IRQ071_Handler(void);
    extern void IRQ072_Handler(void);
    extern void IRQ073_Handler(void);
    extern void IRQ074_Handler(void);
    extern void IRQ075_Handler(void);
    extern void IRQ076_Handler(void);
    extern void IRQ077_Handler(void);
    extern void IRQ078_Handler(void);
    extern void IRQ079_Handler(void);
    extern void IRQ080_Handler(void);
    extern void IRQ081_Handler(void);
    extern void IRQ082_Handler(void);
    extern void IRQ083_Handler(void);
    extern void IRQ084_Handler(void);
    extern void IRQ085_Handler(void);
    extern void IRQ086_Handler(void);
    extern void IRQ087_Handler(void);
    extern void IRQ088_Handler(void);
    extern void IRQ089_Handler(void);
    extern void IRQ090_Handler(void);
    extern void IRQ091_Handler(void);
    extern void IRQ092_Handler(void);
    extern void IRQ093_Handler(void);
    extern void IRQ094_Handler(void);
    extern void IRQ095_Handler(void);
    extern void IRQ096_Handler(void);
    extern void IRQ097_Handler(void);
    extern void IRQ098_Handler(void);
    extern void IRQ099_Handler(void);
    extern void IRQ100_Handler(void);
    extern void IRQ101_Handler(void);
    extern void IRQ102_Handler(void);
    extern void IRQ103_Handler(void);
    extern void IRQ104_Handler(void);
    extern void IRQ105_Handler(void);
    extern void IRQ106_Handler(void);
    extern void IRQ107_Handler(void);
    extern void IRQ108_Handler(void);
    extern void IRQ109_Handler(void);
    extern void IRQ110_Handler(void);
    extern void IRQ111_Handler(void);
    extern void IRQ112_Handler(void);
    extern void IRQ113_Handler(void);
    extern void IRQ114_Handler(void);
    extern void IRQ115_Handler(void);
    extern void IRQ116_Handler(void);
    extern void IRQ117_Handler(void);
    extern void IRQ118_Handler(void);
    extern void IRQ119_Handler(void);
    extern void IRQ120_Handler(void);
    extern void IRQ121_Handler(void);
    extern void IRQ122_Handler(void);
    extern void IRQ123_Handler(void);
    extern void IRQ124_Handler(void);
    extern void IRQ125_Handler(void);
    extern void IRQ126_Handler(void);
    extern void IRQ127_Handler(void);
    extern void IRQ128_Handler(void);
    extern void IRQ129_Handler(void);
    extern void IRQ130_Handler(void);
    extern void IRQ131_Handler(void);
    extern void IRQ132_Handler(void);
    extern void IRQ133_Handler(void);
    extern void IRQ134_Handler(void);
    extern void IRQ135_Handler(void);
    extern void IRQ136_Handler(void);
    extern void IRQ137_Handler(void);
    extern void IRQ138_Handler(void);
    extern void IRQ139_Handler(void);
    extern void IRQ140_Handler(void);
    extern void IRQ141_Handler(void);
    extern void IRQ142_Handler(void);
    extern void IRQ143_Handler(void);
}

vector_table_t vector_table __attribute__((section(".vectors"), aligned(2))) =
    {
        .stackTop = &__StackTop,
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

        // IRQs
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