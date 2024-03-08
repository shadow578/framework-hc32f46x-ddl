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


                .syntax     unified
                .arch       armv7e-m
                .cpu        cortex-m4
                .fpu        softvfp
                .thumb


/*
;<h> Reset handler start.
*/
                .section    .text.Reset_Handler_C
                .align      2
                .weak       Reset_Handler_C
                .type       Reset_Handler_C, %function
                .globl      Reset_Handler_C
Reset_Handler_C:
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
                .size       Reset_Handler_C, . - Reset_Handler_C
/*
;<h> Reset handler end.
*/
