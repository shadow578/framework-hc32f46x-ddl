/*
;*******************************************************************************
; * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
; *
; * This software component is licensed by HDSC under BSD 3-Clause license
; * (the "License"); You may not use this file except in compliance with the
; * License. You may obtain a copy of the License at:
; *                    opensource.org/licenses/BSD-3-Clause
*/
/*****************************************************************************/
/*  Startup for GCC                                                          */
/*  Version     V1.0                                                         */
/*  Date        2019-03-13                                                   */
/*  Target-mcu  HC32F460                                                     */
/*****************************************************************************/

/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
#ifndef DDL_STACK_SIZE
#define DDL_STACK_SIZE 0x00000400
#endif

#ifndef DDL_HEAP_SIZE
#define DDL_HEAP_SIZE 0x00000C00
#endif

                .syntax     unified
                .arch       armv7e-m
                .cpu        cortex-m4
                .fpu        softvfp
                .thumb

/*
;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ        Stack_Size, DDL_STACK_SIZE

                .section    .stack
                .align      3
                .globl      __StackTop
                .globl      __StackLimit
__StackLimit:
                .space      Stack_Size
                .size       __StackLimit, . - __StackLimit
__StackTop:
                .size       __StackTop, . - __StackTop


/*
;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ        Heap_Size, DDL_HEAP_SIZE

                .if         Heap_Size != 0                     /* Heap is provided */
                .section    .heap
                .align      3
                .globl      __HeapBase
                .globl      __HeapLimit
__HeapBase:
                .space      Heap_Size
                .size       __HeapBase, . - __HeapBase
__HeapLimit:
                .size       __HeapLimit, . - __HeapLimit
                .endif

/*
;<h> Reset handler start.
*/
                .section    .text.Reset_Handler
                .align      2
                .weak       Reset_Handler
                .type       Reset_Handler, %function
                .globl      Reset_Handler
Reset_Handler:
                /* Set stack top pointer. */
                ldr         sp, =__StackTop
/* Single section scheme.
 *
 * The ranges of copy from/to are specified by following symbols
 *   __etext: LMA of start of the section to copy from. Usually end of text
 *   __data_start__: VMA of start of the section to copy to
 *   __data_end__: VMA of end of the section to copy to
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
                /* Copy data from read only memory to RAM. */
CopyData:
                ldr         r1, =__etext
                ldr         r2, =__data_start__
                ldr         r3, =__data_end__
CopyLoop:
                cmp         r2, r3
                ittt        lt
                ldrlt       r0, [r1], #4
                strlt       r0, [r2], #4
                blt         CopyLoop

CopyData1:
                ldr         r1, =__etext_ret_ram
                ldr         r2, =__data_start_ret_ram__
                ldr         r3, =__data_end_ret_ram__
CopyLoop1:
                cmp         r2, r3
                ittt        lt
                ldrlt       r0, [r1], #4
                strlt       r0, [r2], #4
                blt         CopyLoop1

/* This part of work usually is done in C library startup code.
 * Otherwise, define this macro to enable it in this startup.
 *
 * There are two schemes too.
 * One can clear multiple BSS sections. Another can only clear one section.
 * The former is more size expensive than the latter.
 *
 * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
 */
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
                /* Clear BSS section. */
ClearBss:
                ldr         r1, =__bss_start__
                ldr         r2, =__bss_end__

                movs        r0, 0
ClearLoop:
                cmp         r1, r2
                itt         lt
                strlt       r0, [r1], #4
                blt         ClearLoop

ClearBss1:
                ldr         r1, =__bss_start_ret_ram__
                ldr         r2, =__bss_end_ret_ram__

                movs        r0, 0
ClearLoop1:
                cmp         r1, r2
                itt         lt
                strlt       r0, [r1], #4
                blt         ClearLoop1

SetSRAM3Wait:
                ldr         r0, =0x40050804
                mov         r1, #0x77
                str         r1, [r0]

                ldr         r0, =0x4005080C
                mov         r1, #0x77
                str         r1, [r0]

                ldr         r0, =0x40050800
                mov         r1, #0x1100
                str         r1, [r0]

                ldr         r0, =0x40050804
                mov         r1, #0x76
                str         r1, [r0]

                ldr         r0, =0x4005080C
                mov         r1, #0x76
                str         r1, [r0]

                /* Call the clock system initialization function. */
                bl          SystemInit
                /* call __libc_init_array before calling main */
                bl          __libc_init_array
                /* Call the application's entry point. */
                bl          main
                bx          lr
                .size       Reset_Handler, . - Reset_Handler
/*
;<h> Reset handler end.
*/

/*
;<h> Default handler start.
*/
                .section    .text.Default_Handler, "ax", %progbits
                .align      2
Default_Handler:
                b           .
                .size       Default_Handler, . - Default_Handler
/*
;<h> Default handler end.
*/

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro      Set_Default_Handler  Handler_Name
                .weak       \Handler_Name
                .set        \Handler_Name, Default_Handler
                .endm

/* Default exception/interrupt handler */

                Set_Default_Handler    NMI_Handler
                Set_Default_Handler    HardFault_Handler
                Set_Default_Handler    MemManage_Handler
                Set_Default_Handler    BusFault_Handler
                Set_Default_Handler    UsageFault_Handler
                Set_Default_Handler    SVC_Handler
                Set_Default_Handler    DebugMon_Handler
                Set_Default_Handler    PendSV_Handler
                Set_Default_Handler    SysTick_Handler

                Set_Default_Handler    IRQ000_Handler
                Set_Default_Handler    IRQ001_Handler
                Set_Default_Handler    IRQ002_Handler
                Set_Default_Handler    IRQ003_Handler
                Set_Default_Handler    IRQ004_Handler
                Set_Default_Handler    IRQ005_Handler
                Set_Default_Handler    IRQ006_Handler
                Set_Default_Handler    IRQ007_Handler
                Set_Default_Handler    IRQ008_Handler
                Set_Default_Handler    IRQ009_Handler
                Set_Default_Handler    IRQ010_Handler
                Set_Default_Handler    IRQ011_Handler
                Set_Default_Handler    IRQ012_Handler
                Set_Default_Handler    IRQ013_Handler
                Set_Default_Handler    IRQ014_Handler
                Set_Default_Handler    IRQ015_Handler
                Set_Default_Handler    IRQ016_Handler
                Set_Default_Handler    IRQ017_Handler
                Set_Default_Handler    IRQ018_Handler
                Set_Default_Handler    IRQ019_Handler
                Set_Default_Handler    IRQ020_Handler
                Set_Default_Handler    IRQ021_Handler
                Set_Default_Handler    IRQ022_Handler
                Set_Default_Handler    IRQ023_Handler
                Set_Default_Handler    IRQ024_Handler
                Set_Default_Handler    IRQ025_Handler
                Set_Default_Handler    IRQ026_Handler
                Set_Default_Handler    IRQ027_Handler
                Set_Default_Handler    IRQ028_Handler
                Set_Default_Handler    IRQ029_Handler
                Set_Default_Handler    IRQ030_Handler
                Set_Default_Handler    IRQ031_Handler
                Set_Default_Handler    IRQ032_Handler
                Set_Default_Handler    IRQ033_Handler
                Set_Default_Handler    IRQ034_Handler
                Set_Default_Handler    IRQ035_Handler
                Set_Default_Handler    IRQ036_Handler
                Set_Default_Handler    IRQ037_Handler
                Set_Default_Handler    IRQ038_Handler
                Set_Default_Handler    IRQ039_Handler
                Set_Default_Handler    IRQ040_Handler
                Set_Default_Handler    IRQ041_Handler
                Set_Default_Handler    IRQ042_Handler
                Set_Default_Handler    IRQ043_Handler
                Set_Default_Handler    IRQ044_Handler
                Set_Default_Handler    IRQ045_Handler
                Set_Default_Handler    IRQ046_Handler
                Set_Default_Handler    IRQ047_Handler
                Set_Default_Handler    IRQ048_Handler
                Set_Default_Handler    IRQ049_Handler
                Set_Default_Handler    IRQ050_Handler
                Set_Default_Handler    IRQ051_Handler
                Set_Default_Handler    IRQ052_Handler
                Set_Default_Handler    IRQ053_Handler
                Set_Default_Handler    IRQ054_Handler
                Set_Default_Handler    IRQ055_Handler
                Set_Default_Handler    IRQ056_Handler
                Set_Default_Handler    IRQ057_Handler
                Set_Default_Handler    IRQ058_Handler
                Set_Default_Handler    IRQ059_Handler
                Set_Default_Handler    IRQ060_Handler
                Set_Default_Handler    IRQ061_Handler
                Set_Default_Handler    IRQ062_Handler
                Set_Default_Handler    IRQ063_Handler
                Set_Default_Handler    IRQ064_Handler
                Set_Default_Handler    IRQ065_Handler
                Set_Default_Handler    IRQ066_Handler
                Set_Default_Handler    IRQ067_Handler
                Set_Default_Handler    IRQ068_Handler
                Set_Default_Handler    IRQ069_Handler
                Set_Default_Handler    IRQ070_Handler
                Set_Default_Handler    IRQ071_Handler
                Set_Default_Handler    IRQ072_Handler
                Set_Default_Handler    IRQ073_Handler
                Set_Default_Handler    IRQ074_Handler
                Set_Default_Handler    IRQ075_Handler
                Set_Default_Handler    IRQ076_Handler
                Set_Default_Handler    IRQ077_Handler
                Set_Default_Handler    IRQ078_Handler
                Set_Default_Handler    IRQ079_Handler
                Set_Default_Handler    IRQ080_Handler
                Set_Default_Handler    IRQ081_Handler
                Set_Default_Handler    IRQ082_Handler
                Set_Default_Handler    IRQ083_Handler
                Set_Default_Handler    IRQ084_Handler
                Set_Default_Handler    IRQ085_Handler
                Set_Default_Handler    IRQ086_Handler
                Set_Default_Handler    IRQ087_Handler
                Set_Default_Handler    IRQ088_Handler
                Set_Default_Handler    IRQ089_Handler
                Set_Default_Handler    IRQ090_Handler
                Set_Default_Handler    IRQ091_Handler
                Set_Default_Handler    IRQ092_Handler
                Set_Default_Handler    IRQ093_Handler
                Set_Default_Handler    IRQ094_Handler
                Set_Default_Handler    IRQ095_Handler
                Set_Default_Handler    IRQ096_Handler
                Set_Default_Handler    IRQ097_Handler
                Set_Default_Handler    IRQ098_Handler
                Set_Default_Handler    IRQ099_Handler
                Set_Default_Handler    IRQ100_Handler
                Set_Default_Handler    IRQ101_Handler
                Set_Default_Handler    IRQ102_Handler
                Set_Default_Handler    IRQ103_Handler
                Set_Default_Handler    IRQ104_Handler
                Set_Default_Handler    IRQ105_Handler
                Set_Default_Handler    IRQ106_Handler
                Set_Default_Handler    IRQ107_Handler
                Set_Default_Handler    IRQ108_Handler
                Set_Default_Handler    IRQ109_Handler
                Set_Default_Handler    IRQ110_Handler
                Set_Default_Handler    IRQ111_Handler
                Set_Default_Handler    IRQ112_Handler
                Set_Default_Handler    IRQ113_Handler
                Set_Default_Handler    IRQ114_Handler
                Set_Default_Handler    IRQ115_Handler
                Set_Default_Handler    IRQ116_Handler
                Set_Default_Handler    IRQ117_Handler
                Set_Default_Handler    IRQ118_Handler
                Set_Default_Handler    IRQ119_Handler
                Set_Default_Handler    IRQ120_Handler
                Set_Default_Handler    IRQ121_Handler
                Set_Default_Handler    IRQ122_Handler
                Set_Default_Handler    IRQ123_Handler
                Set_Default_Handler    IRQ124_Handler
                Set_Default_Handler    IRQ125_Handler
                Set_Default_Handler    IRQ126_Handler
                Set_Default_Handler    IRQ127_Handler
                Set_Default_Handler    IRQ128_Handler
                Set_Default_Handler    IRQ129_Handler
                Set_Default_Handler    IRQ130_Handler
                Set_Default_Handler    IRQ131_Handler
                Set_Default_Handler    IRQ132_Handler
                Set_Default_Handler    IRQ133_Handler
                Set_Default_Handler    IRQ134_Handler
                Set_Default_Handler    IRQ135_Handler
                Set_Default_Handler    IRQ136_Handler
                Set_Default_Handler    IRQ137_Handler
                Set_Default_Handler    IRQ138_Handler
                Set_Default_Handler    IRQ139_Handler
                Set_Default_Handler    IRQ140_Handler
                Set_Default_Handler    IRQ141_Handler
                Set_Default_Handler    IRQ142_Handler
                Set_Default_Handler    IRQ143_Handler

                .end
