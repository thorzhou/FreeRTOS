#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_16BIT_TICKS   0
#define configMAX_TASK_NAME_LEN 16 //任务名称最大长度

#define configSUPPORT_STATIC_ALLOCATION   1 //是否允许静态创建任务
#define configMAX_PRIORITIES 5 //最大任务优先级 默认5最大256

#define configKERNEL_INTERRUPT_PRIORITY 255 //中断优先级配置
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 191 //配置中断屏蔽寄存器BASEPRI的值，高4位有效。目前191，实际值11，优先级高于或者等于11的中断都将被屏蔽。

#define configMINIMAL_STACK_SIZE    ((unsigned short) 128)

#define configCPU_CLOCK_HZ  ((unsigned long) 25000000)
#define configTICK_RATE_HZ  ((TickType_t) 100)

#define xPortPendSVHandler   PendSV_Handler
#define xPortSysTickHandler  SysTick_Handler
#define vPortSVCHandler      SVC_Handler

#endif /*FREERTOS_CONFIG_H*/
