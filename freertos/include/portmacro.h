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

/* 不带返回值的关中断函数，不能嵌套，不能在中断里面使用 */
#define portDISABLE_INTERRUPTS()    vPortRaiseBASEPRI()
void vPortRaiseBASEPRI(void)
{
    uint32_t ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;
    __asm
    {
        msr basepri, ulNewBASEPRI
        dsb
        isb
    }
}

/* 带返回值的关中断函数，可以嵌套，可以在中断里面使用 */
#define portSET_INTERRUPT_MASK_FROM_ISR() ulPortRaiseBASEPRI()
uint32_t ulPortRaiseBASEPRI(void)
{
    uint32_t ulReturn, ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;
    __asm
    {
        mrs ulReturn, basepri
        msr basepri, ulNewBASEPRI
        dsb
        isb
    }
    return ulReturn;
}

/* 开中断 */
extern vPortEnterCritical(void);
extern vPortExitCritical(void);

// #define portENABLE_INTERRUPTS() vPortSetBASEPRI( 0 )
// #define portCLEAR_INTERRUPT_MASK_FROM_ISR(x) vPortSetBASEPRI(x)
void vPortSetBASEPRI(uint32_t ulBASEPRI)
{
    __asm
    {
        msr basepri, ulBASEPRI
    }
}
#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()

/* without return */
#define portDISABLE_INTERRUPTS()    vPortRaiseBASEPRI()
/* 不带中断保护的开中断函数,根据传参,与不带返回值的关中断函数配套使用 */
#define portENABLE_INTERRUPTS() vPortSetBASEPRI(0)
/* with return */
#define portSET_INTERRUPT_MASK_FROM_ISR() ulPortRaiseBASEPRI()
/* 带中断保护的开中断函数，与带返回值的关中断函数一起使用 */
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x) vPortSetBASEPRI(x)

#define portINLINE __inline

#ifndef portFORCE_INLINE
	#define portFORCE_INLINE __forceinline
#endif

/* without return */
static portFORCE_INLINE void vPortRaiseBASEPRI(void)
{
    uint32_t ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;
    __asm
    {
        msr basepri, ulNewBASEPRI
        dsb
        isb
    }
}

static portFORCE_INLINE void vPortSetBASEPRI(uint32_t ulBASEPRI)
{
    __asm
    {
        msr basepri, ulBASEPRI
    }
}

/* with return */
static portFORCE_INLINE uint32_t ulPortRaiseBASEPRI(void)
{
    uint32_t ulReturn, ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;
    __asm
    {
        mrs ulReturn, basepri
        msr basepri, ulNewBASEPRI
        dsb
        isb
    }
    return ulReturn;
}

static portFORCE_INLINE void vPortSetBASEPRI(uint32_t ulBASEPRI)
{
    __asm
    {
        msr basepri, ulBASEPRI
    }
}
#endif /*PORTMACRO_H*/
