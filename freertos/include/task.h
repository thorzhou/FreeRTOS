#ifndef INC_TASK_H
#define INC_TASK_H

#include "FreeRTOS.h"
#include "list.h"

/* 任务句柄 */
typedef void *TaskHandle_t;

/* 任务切换 */
#define taskYIELD()     portYIELD()

#if(configSUPPORT_STATIC_ALLOCATION == 1)
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,          //任务入口，即函数名称，
                                const char * const pcName,          //任务名称，string，方便调试
                                const uint32_t ulStackDepth,        //任务栈大小，unit：4byte
                                void *const pvParameters,           //任务形参
                                StackType_t *const puxStackBuffer,  //任务栈起始地址
                                TCB_t *const pxTaskBuffer );        //TCB指针
#endif 

void prvInitialiseTaskLists(void);
void vTaskStartScheduler(void);
void vTaskSwitchContext(void);

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
BaseType_t xPortStartScheduler( void );

/* 进入临界段 */
/* 不带中断保护，不能嵌套 */
#define taskENTER_CRITICAL()    portENTER_CRITICAL()
#define taskEXIT_CRITICAL()     portEXIT_CRITICAL()
/* 带中断保护，能嵌套 */
#define taskENTER_CRITICAL_FROM_ISR()   portSET_INTERRUPT_MASK_FROM_ISR()
#define taskEXIT_CRITICAL_FROM_ISR(x)    portCLEAR_INTERRUPT_MASK_FROM_ISR(x)

#endif /*INC_TASK_H*/
