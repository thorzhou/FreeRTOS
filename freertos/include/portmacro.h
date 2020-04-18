#ifndef PORTMACRO_H
#define PORTMACRO_H

#include "stdint.h"
#include "stddef.h"

#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   long

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if(configUSE_16_BIT_TICKS == 1)
    typedef uint16_t TickType_t;
    #define portMAX_DELAY (TickType_t) 0xffff
#else
    typedef uint32_t TickType_t;
    #define portMAX_DELAY (TickType_t) 0xffffffffUL
#endif

/* 
 * 中断控制状态寄存器：0xE000ED04
 * Bit 28 PENDSVSET: PendSV 悬起位
 */
#define portNVIC_INT_CTRL_REG   (*((volatile uint32_t *) 0xE000ED04))
#define portNVIC_PENDSVSET_BIT  (1UL << 28UL )
#define portSY_FULL_READ_WRITE  (15)

/* YIELD的实现就是将PendSV的悬起位置1，当没有其他中断运行的时候响应PendSV中断，去执行PendSV中断服务函数，在中断里实现任务切换 */
#define portYIELD()                                 \
{                                                   \
    /* 触发PendSV，产生上下文切换 */                 \
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
    __dsb(portSY_FULL_READ_WRITE);                  \
    __isb(portSY_FULL_READ_WRITE);                  \
}

#endif /*PORTMACRO_H*/
