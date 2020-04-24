/*
*************************************************************************
*                             Include
*************************************************************************
*/
#include "task.h"
/*
*************************************************************************
*                             Macro
*************************************************************************
*/
// /* TCB type definition */
// typedef struct tskTaskControlBlock
// {
//     volatile StackType_t *pxTopOfStack;         //栈顶
//     ListItem_t xStateListItem;                  //任务节点
//     StackType_t *pxStack;                       //任务栈起始地址
//     char pcTaskName[configMAX_TASK_NAME_LEN];   //任务名称，字符串
// }tskTCB;
// typedef tskTCB TCB_t;
/*
*************************************************************************
*                             Declaration
*************************************************************************
*/
/* 创建任务 */
static void prvInitialiseNewTask(TaskFunction_t pxTaskCode, //entry
                                 const char *const pcName,
                                 const uint32_t ulStackDepth,
                                 void *const pvParameters,
                                 TaskHandle_t *const pxCreatedTask,
                                 TCB_t *pxNewTCB);

extern TCB_t IdleTaskTCB;
void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize );
/*
*************************************************************************
*                             Global variable
*************************************************************************
*/
/* 用于指向当前正在运行或者即将要运行的任务的TCB */
TCB_t *volatile pxCurrentTCB = NULL;
/* 任务就绪列表 */
List_t pxReadyTasksLists[configMAX_PRIORITIES];

static volatile UBaseType_t uxCurrentNumberOfTasks = (UBaseType_t)0U;

/*
** 
**                      创建任务，联系任务栈，任务函数实体，任务的TCB   
**
*/
#if (configSUPPORT_STATIC_ALLOCATION == 1)
TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,         //任务入口，即函数名称，
                               const char *const pcName,          //任务名称，string，方便调试
                               const uint32_t ulStackDepth,       //任务栈大小，unit：4byte
                               void *const pvParameters,          //任务形参
                               StackType_t *const puxStackBuffer, //任务栈起始地址
                               TCB_t *const pxTaskBuffer)         //TCB指针
{
    TCB_t *pxNewTCB;
    TaskHandle_t xReturn; //定义任务句柄，指向TCB，定义在task.h中

    if ((pxTaskBuffer != NULL) && (puxStackBuffer != NULL))
    {
        pxNewTCB = (TCB_t *)pxTaskBuffer;
        pxNewTCB->pxStack = (StackType_t *)puxStackBuffer; //设定任务栈起始地址
        /* 创建新的任务 */
        prvInitialiseNewTask(pxTaskCode,   //任务入口
                             pcName,       //任务名称，string
                             ulStackDepth, //任务栈大小，4byte
                             pvParameters, //任务形参
                             &xReturn,     //任务句柄
                             pxNewTCB);    //任务栈起始地址
    }
    else
    {
        xReturn = NULL;
    }
    /* 返回任务句柄，如果成功创建任务，此时xReturn指向任务控制块 */
    return xReturn;
}
#endif /*configSUPPORT_STATIC_ALLOCATION*/

/* 创建任务 */
static void prvInitialiseNewTask(TaskFunction_t pxTaskCode, //entry
                                 const char *const pcName,
                                 const uint32_t ulStackDepth,
                                 void *const pvParameters,
                                 TaskHandle_t *const pxCreatedTask,
                                 TCB_t *pxNewTCB)
{
    StackType_t *pxTopOfStack;
    UBaseType_t x;
    /* 获取栈顶地址 */
    pxTopOfStack = pxNewTCB->pxStack + (ulStackDepth - (uint32_t)1);
    /* 向下做8byte对齐 */
    pxTopOfStack = (StackType_t *)(((uint32_t)pxTopOfStack) & (~((uint32_t)0x0007)));

    /* 将任务的名字存储在TCB中 */
    for (x = (UBaseType_t)0; x < (UBaseType_t)configMAX_TASK_NAME_LEN; x++)
    {
        pxNewTCB->pcTaskName[x] = pcName[x];
        if (pcName[x] == 0x00)
        {
            break;
        }
    }
    /* 任务名字的长度不能超过configMAX_TASK_NAME_LEN */
    pxNewTCB->pcTaskName[configMAX_TASK_NAME_LEN - 1] = '\0';

    /* 初始化TCB中的xStateListItem节点 */
    vListInitialiseItem(&(pxNewTCB->xStateListItem));
    /* 设置节点拥有者 */
    listSET_LIST_ITEM_OWNER(&(pxNewTCB->xStateListItem), pxNewTCB);

    /* 初始化任务栈 */
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pxTaskCode, pvParameters);
    /* 让任务句柄指向TCB */
    if ((void *)pxCreatedTask != NULL)
    {
        *pxCreatedTask = (TaskHandle_t)pxNewTCB;
    }
}

/* 初始化就绪列表 */
void prvInitialiseTaskLists(void)
{
    UBaseType_t uxPriority;

    for (uxPriority = (UBaseType_t)0U;
         uxPriority < (UBaseType_t)configMAX_PRIORITIES;
         uxPriority++)
    {
        vListInitialise(&(pxReadyTasksLists[uxPriority]));
    }
}

extern TCB_t Task1TCB;
extern TCB_t Task2TCB;
extern TickType_t xTickCount;
/* 启动调度器 */
void vTaskStartScheduler(void)
{
    /*=================== 创建空闲任务 =====================*/
    TCB_t *pxIdleTaskTCBBuffer = NULL;  //指向空闲任务控制块
    StackType_t *pxIdleTaskStackBuffer = NULL;  //指向空闲任务栈起始地址
    uint32_t ulIdleTaskStackSize;
    /* 获取空闲任务的内存：任务栈和TCB */
    vApplicationGetIdleTaskMemory(  &pxIdleTaskTCBBuffer,
                                    &pxIdleTaskStackBuffer,
                                    &ulIdleTaskStackSize);
    /* 创建空闲任务 */
    xIdleTaskHandle = xTaskCreateStatic( (TaskFunction_t)prvIdleTask,
                                         (char*)"IDLE",
                                         (uint32_t)ulIdleTaskStackSize,
                                         (void *)NULL,  //任务形参
                                         (StackType_t *)pxIdleTaskStackBuffer,
                                         (TCB_t *)pxIdleTaskTCBBuffer );
    vListInsertEnd(&(pxReadyTasksLists[0]),&(((TCB_t *)pxIdleTaskTCBBuffer)->xStateListItem));
    /*=================== End of 创建空闲任务 =============*/

    /* 手动指定第一个运行的任务，因为现在还不支持优先级 */
    pxCurrentTCB = &Task1TCB;

    xTickCount = 0;
    /* 启动调度器 */
    if (xPortStartScheduler() != pdFALSE)
    {
        /* 调度器启动成功，则不会返回，即不会来到这里 */
    }
}

/* 选择优先级最高的任务 */
#if 0
void vTaskSwitchContext(void)
{
    /* 两个任务轮流切换 */
    if (pxCurrentTCB == &Task1TCB)
    {
        pxCurrentTCB = &Task2TCB;
    }
    else
    {
        pxCurrentTCB = &Task1TCB;
    }
}
#else
void vTaskSwitchContext(void)
{
    /* 如果当前任务式空闲任务，那么就去尝试执行任务1或者任务2，看看他们的
    延时时间是否结束，如果任务的延时时间均没有到期，那就返回继续执行空闲任务 */
    if(pxCurrentTCB == &IdleTaskTCB)
    {
        if(Task1TCB.xTicksToDelay == 0)
        {
            pxCurrentTCB = &Task1TCB;
        }
        else if(Task2TCB.xTicksToDelay == 0)
        {
            pxCurrentTCB = &Task2TCB;
        }
        else
        {
            return;
        }
    }
    else //当前不是执行空闲任务
    {
        /* 如果当前任务是任务1或者任务2的话，检查下另外一个任务，如果
        另外的任务不在延时中，就切换到该任务，否则，判断下当前任务是否
        应该进入延时状态，如果是，就切换到空闲任务，否则就不进行切换 */
        if(pxCurrentTCB == &Task1TCB)
        {
            if(Task2TCB.xTicksToDelay == 0)
            {
                pxCurrentTCB = &Task2TCB;
            }
            else if(pxCurrentTCB->xTicksToDelay != 0)
            {
                pxCurrentTCB = &IdleTaskTCB;
            }
            else
            {
                return;
            }
        }
        else if(pxCurrentTCB == &Task2TCB)
        {
            if(Task1TCB.xTicksToDelay == 0)
            {
                pxCurrentTCB = &Task1TCB;
            }
            else if(pxCurrentTCB->xTicksToDelay != 0)
            {
                pxCurrentTCB = &IdleTaskTCB;
            }
            else
            {
                return;
            }
        }
    }
}
#endif

/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
void xTaskIncrementTick(void)
{
    TCB_t *pxTCB = NULL;
    BaseType_t i = 0;
    
    /* 更新系统时基计数器xTickCount,定义再port.c中的全局变量 */
    const TickType_t xConstTickCount = xTickCount + 1;
    xTickCount = xConstTickCount;

    /* 扫描就绪列表中所有任务的xTicksToDelay,如果不为0，则减1 */
    for (i = 0; i < configMAX_PRIORITIES; i++)
    {
        pxTCB = (TCB_t *)listGET_OWNER_OF_HEAD_ENTRY((&pxReadyTasksLists[i]));
        if(pxTCB->xTicksToDelay > 0)
        {
            pxTCB->xTicksToDelay--;
        }
    }
    
    /* 任务切换 */
    portYIELD();
}

