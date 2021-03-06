/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 */
#include <rtthread.h>
#include "LPC24xx.h"

/**
 * @addtogroup LPC2478
 */
/*@{*/

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t* rt_hw_stack_init(void* tentry, void* parameter,
                             rt_uint8_t* stack_addr, void* texit)
{
	rt_uint32_t* stk;

	stack_addr += sizeof(rt_uint32_t);
	stack_addr  = (rt_uint8_t*)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
	stk      = (rt_uint32_t*)stack_addr;

	*(--stk) = (rt_uint32_t)tentry;         /* entry point */
	*(--stk) = (rt_uint32_t)texit;          /* lr */
	*(--stk) = 0xdeadbeef;                  /* r12 */
	*(--stk) = 0xdeadbeef;                  /* r11 */
	*(--stk) = 0xdeadbeef;                  /* r10 */
	*(--stk) = 0xdeadbeef;                  /* r9 */
	*(--stk) = 0xdeadbeef;                  /* r8 */
	*(--stk) = 0xdeadbeef;                  /* r7 */
	*(--stk) = 0xdeadbeef;                  /* r6 */
	*(--stk) = 0xdeadbeef;                  /* r5 */
	*(--stk) = 0xdeadbeef;                  /* r4 */
	*(--stk) = 0xdeadbeef;                  /* r3 */
	*(--stk) = 0xdeadbeef;                  /* r2 */
	*(--stk) = 0xdeadbeef;                  /* r1 */
	*(--stk) = (rt_uint32_t)parameter;      /* r0 : argument */

	/* cpsr */
	if((rt_uint32_t)tentry & 0x01)
		*(--stk) = SVCMODE | 0x20;          /* thumb mode */
	else
		*(--stk) = SVCMODE;                 /* arm mode   */

	/* return task's current stack address */
	return (rt_uint8_t*)stk;
}

/*@}*/
