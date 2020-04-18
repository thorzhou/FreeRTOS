#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include "FreeRTOSConfig.h"
#include "portable.h"
#include "projdefs.h"
#include "list.h"

/* TCB type definition */
typedef struct tskTaskControlBlock
{
    volatile StackType_t *pxTopOfStack;         //栈顶
    ListItem_t xStateListItem;                  //任务节点
    StackType_t *pxStack;                       //任务栈起始地址
    char pcTaskName[configMAX_TASK_NAME_LEN];   //任务名称，字符串
}tskTCB;
typedef tskTCB TCB_t;

#endif /*INC_FREERTOS_H*/
