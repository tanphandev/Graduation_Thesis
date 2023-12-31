/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'system'
 * SOPC Builder design path: ../../system.sopcinfo
 *
 * Generated: Sun Jul 02 14:43:19 ICT 2023
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x040c0820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x04080020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x04080000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x040c0820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x04080020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x04080000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_NIOS2_GEN2
#define __SHA_2


/*
 * SHA_0 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_0 SHA_2
#define SHA_0_BASE 0x40c3800
#define SHA_0_IRQ 1
#define SHA_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_0_NAME "/dev/SHA_0"
#define SHA_0_SPAN 1024
#define SHA_0_TYPE "SHA_2"


/*
 * SHA_1 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_1 SHA_2
#define SHA_1_BASE 0x40c3400
#define SHA_1_IRQ 2
#define SHA_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_1_NAME "/dev/SHA_1"
#define SHA_1_SPAN 1024
#define SHA_1_TYPE "SHA_2"


/*
 * SHA_2 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_2 SHA_2
#define SHA_2_BASE 0x40c3000
#define SHA_2_IRQ 3
#define SHA_2_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_2_NAME "/dev/SHA_2"
#define SHA_2_SPAN 1024
#define SHA_2_TYPE "SHA_2"


/*
 * SHA_3 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_3 SHA_2
#define SHA_3_BASE 0x40c2c00
#define SHA_3_IRQ 4
#define SHA_3_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_3_NAME "/dev/SHA_3"
#define SHA_3_SPAN 1024
#define SHA_3_TYPE "SHA_2"


/*
 * SHA_4 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_4 SHA_2
#define SHA_4_BASE 0x40c2800
#define SHA_4_IRQ 5
#define SHA_4_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_4_NAME "/dev/SHA_4"
#define SHA_4_SPAN 1024
#define SHA_4_TYPE "SHA_2"


/*
 * SHA_5 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_5 SHA_2
#define SHA_5_BASE 0x40c2400
#define SHA_5_IRQ 6
#define SHA_5_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_5_NAME "/dev/SHA_5"
#define SHA_5_SPAN 1024
#define SHA_5_TYPE "SHA_2"


/*
 * SHA_6 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_6 SHA_2
#define SHA_6_BASE 0x40c2000
#define SHA_6_IRQ 7
#define SHA_6_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_6_NAME "/dev/SHA_6"
#define SHA_6_SPAN 1024
#define SHA_6_TYPE "SHA_2"


/*
 * SHA_7 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_7 SHA_2
#define SHA_7_BASE 0x40c1c00
#define SHA_7_IRQ 8
#define SHA_7_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_7_NAME "/dev/SHA_7"
#define SHA_7_SPAN 1024
#define SHA_7_TYPE "SHA_2"


/*
 * SHA_8 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_8 SHA_2
#define SHA_8_BASE 0x40c1800
#define SHA_8_IRQ 9
#define SHA_8_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_8_NAME "/dev/SHA_8"
#define SHA_8_SPAN 1024
#define SHA_8_TYPE "SHA_2"


/*
 * SHA_9 configuration
 *
 */

#define ALT_MODULE_CLASS_SHA_9 SHA_2
#define SHA_9_BASE 0x40c1400
#define SHA_9_IRQ 10
#define SHA_9_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SHA_9_NAME "/dev/SHA_9"
#define SHA_9_SPAN 1024
#define SHA_9_TYPE "SHA_2"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x40c3c08
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x40c3c08
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x40c3c08
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "system"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x40c3c08
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x4080000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "system_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 256000
#define ONCHIP_MEMORY2_0_SPAN 256000
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * onchip_memory2_1 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_1 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_1_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_1_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_1_BASE 0x4040000
#define ONCHIP_MEMORY2_1_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_1_DUAL_PORT 0
#define ONCHIP_MEMORY2_1_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_1_INIT_CONTENTS_FILE "system_onchip_memory2_1"
#define ONCHIP_MEMORY2_1_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_1_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_1_IRQ -1
#define ONCHIP_MEMORY2_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_1_NAME "/dev/onchip_memory2_1"
#define ONCHIP_MEMORY2_1_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_1_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_1_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_1_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_1_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_1_SIZE_VALUE 256000
#define ONCHIP_MEMORY2_1_SPAN 256000
#define ONCHIP_MEMORY2_1_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_1_WRITABLE 1


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 67108864
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0

#endif /* __SYSTEM_H_ */
