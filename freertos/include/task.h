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

#endif /*INC_TASK_H*/
