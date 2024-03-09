#include <stdint.h>

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

void *vector_table[] __attribute__((section(".vectors"), aligned(2))) =
    {
        (void *)&__StackTop,
        (void *)Reset_Handler,
        (void *)NMI_Handler,
        (void *)HardFault_Handler,
        (void *)MemManage_Handler,
        (void *)BusFault_Handler,
        (void *)UsageFault_Handler,
        (void *)nullptr,
        (void *)nullptr,
        (void *)nullptr,
        (void *)nullptr,
        (void *)SVC_Handler,
        (void *)DebugMon_Handler,
        (void *)nullptr,
        (void *)PendSV_Handler,
        (void *)SysTick_Handler,

        // IRQs
        (void *)IRQ000_Handler,
        (void *)IRQ001_Handler,
        (void *)IRQ002_Handler,
        (void *)IRQ003_Handler,
        (void *)IRQ004_Handler,
        (void *)IRQ005_Handler,
        (void *)IRQ006_Handler,
        (void *)IRQ007_Handler,
        (void *)IRQ008_Handler,
        (void *)IRQ009_Handler,
        (void *)IRQ010_Handler,
        (void *)IRQ011_Handler,
        (void *)IRQ012_Handler,
        (void *)IRQ013_Handler,
        (void *)IRQ014_Handler,
        (void *)IRQ015_Handler,
        (void *)IRQ016_Handler,
        (void *)IRQ017_Handler,
        (void *)IRQ018_Handler,
        (void *)IRQ019_Handler,
        (void *)IRQ020_Handler,
        (void *)IRQ021_Handler,
        (void *)IRQ022_Handler,
        (void *)IRQ023_Handler,
        (void *)IRQ024_Handler,
        (void *)IRQ025_Handler,
        (void *)IRQ026_Handler,
        (void *)IRQ027_Handler,
        (void *)IRQ028_Handler,
        (void *)IRQ029_Handler,
        (void *)IRQ030_Handler,
        (void *)IRQ031_Handler,
        (void *)IRQ032_Handler,
        (void *)IRQ033_Handler,
        (void *)IRQ034_Handler,
        (void *)IRQ035_Handler,
        (void *)IRQ036_Handler,
        (void *)IRQ037_Handler,
        (void *)IRQ038_Handler,
        (void *)IRQ039_Handler,
        (void *)IRQ040_Handler,
        (void *)IRQ041_Handler,
        (void *)IRQ042_Handler,
        (void *)IRQ043_Handler,
        (void *)IRQ044_Handler,
        (void *)IRQ045_Handler,
        (void *)IRQ046_Handler,
        (void *)IRQ047_Handler,
        (void *)IRQ048_Handler,
        (void *)IRQ049_Handler,
        (void *)IRQ050_Handler,
        (void *)IRQ051_Handler,
        (void *)IRQ052_Handler,
        (void *)IRQ053_Handler,
        (void *)IRQ054_Handler,
        (void *)IRQ055_Handler,
        (void *)IRQ056_Handler,
        (void *)IRQ057_Handler,
        (void *)IRQ058_Handler,
        (void *)IRQ059_Handler,
        (void *)IRQ060_Handler,
        (void *)IRQ061_Handler,
        (void *)IRQ062_Handler,
        (void *)IRQ063_Handler,
        (void *)IRQ064_Handler,
        (void *)IRQ065_Handler,
        (void *)IRQ066_Handler,
        (void *)IRQ067_Handler,
        (void *)IRQ068_Handler,
        (void *)IRQ069_Handler,
        (void *)IRQ070_Handler,
        (void *)IRQ071_Handler,
        (void *)IRQ072_Handler,
        (void *)IRQ073_Handler,
        (void *)IRQ074_Handler,
        (void *)IRQ075_Handler,
        (void *)IRQ076_Handler,
        (void *)IRQ077_Handler,
        (void *)IRQ078_Handler,
        (void *)IRQ079_Handler,
        (void *)IRQ080_Handler,
        (void *)IRQ081_Handler,
        (void *)IRQ082_Handler,
        (void *)IRQ083_Handler,
        (void *)IRQ084_Handler,
        (void *)IRQ085_Handler,
        (void *)IRQ086_Handler,
        (void *)IRQ087_Handler,
        (void *)IRQ088_Handler,
        (void *)IRQ089_Handler,
        (void *)IRQ090_Handler,
        (void *)IRQ091_Handler,
        (void *)IRQ092_Handler,
        (void *)IRQ093_Handler,
        (void *)IRQ094_Handler,
        (void *)IRQ095_Handler,
        (void *)IRQ096_Handler,
        (void *)IRQ097_Handler,
        (void *)IRQ098_Handler,
        (void *)IRQ099_Handler,
        (void *)IRQ100_Handler,
        (void *)IRQ101_Handler,
        (void *)IRQ102_Handler,
        (void *)IRQ103_Handler,
        (void *)IRQ104_Handler,
        (void *)IRQ105_Handler,
        (void *)IRQ106_Handler,
        (void *)IRQ107_Handler,
        (void *)IRQ108_Handler,
        (void *)IRQ109_Handler,
        (void *)IRQ110_Handler,
        (void *)IRQ111_Handler,
        (void *)IRQ112_Handler,
        (void *)IRQ113_Handler,
        (void *)IRQ114_Handler,
        (void *)IRQ115_Handler,
        (void *)IRQ116_Handler,
        (void *)IRQ117_Handler,
        (void *)IRQ118_Handler,
        (void *)IRQ119_Handler,
        (void *)IRQ120_Handler,
        (void *)IRQ121_Handler,
        (void *)IRQ122_Handler,
        (void *)IRQ123_Handler,
        (void *)IRQ124_Handler,
        (void *)IRQ125_Handler,
        (void *)IRQ126_Handler,
        (void *)IRQ127_Handler,
        (void *)IRQ128_Handler,
        (void *)IRQ129_Handler,
        (void *)IRQ130_Handler,
        (void *)IRQ131_Handler,
        (void *)IRQ132_Handler,
        (void *)IRQ133_Handler,
        (void *)IRQ134_Handler,
        (void *)IRQ135_Handler,
        (void *)IRQ136_Handler,
        (void *)IRQ137_Handler,
        (void *)IRQ138_Handler,
        (void *)IRQ139_Handler,
        (void *)IRQ140_Handler,
        (void *)IRQ141_Handler,
        (void *)IRQ142_Handler,
        (void *)IRQ143_Handler,
};