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
