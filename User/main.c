/** @defgroup <Module_Name>
 *  @addtogroup <Module_Name>(If this is a sub-module, add it father module here)
 *  @design <Document link>
 *  @testspec <Document link>
 *
 *  @{
 */
//------------------------------------------------------------------------------
//  $Header$
//
//  Company    : Suzhou Naxin New Energy Technology, Co., Ltd.
//
//  Project    : P1001
//
//  Filename   : 
//
//  Programmer : Author
//                             
//  Description   : "file description" 
//
//              ***  Confidential property of Company name ***
//                             Copyright(c) Company name, 2020
//------------------------------------------------------------------------------

//-------------------- pragmas ----------------------------------------------

//-------------------- include files ----------------------------------------
#include "FreeRTOS.h"
#include "task.h"
//-------------------- local definitions ------------------------------------
// /* 定义空闲任务的栈 */
// #define configMINIMAL_STACK_SIZE ((unsigned short)128)

//-------------------- private data -----------------------------------------
/* 空闲任务的栈是一个定义好的数组，大小由configMINIMAL_STACK_SIZE控制，默认512字节 */
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
/* 定义空闲任务的TCB */
TCB_t IdleTaskTCB;
//-------------------- private functions declare ----------------------------

//-------------------- public data ------------------------------------------

//-------------------- public functions -------------------------------------
/*! \fn			void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer,
 *                                   StackType_t **ppxIdleTaskStackBuffer,
 *                                   uint32_t *pulIdleTaskStackSize)
 *  \brief 		设置形参指针指向IDLE任务的TCB和栈起始地址
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	NONE
 */
void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &IdleTaskTCB;
    *ppxIdleTaskStackBuffer = IdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/*! \fn			void vTaskDelay(const TickType_t xTicksToDelay)
 *  \brief 		blocking delay
 *  \param 		param1: delay time
 *  \exception (None non-reentrant code)
 *  \return 	NONE
 */
void vTaskDelay(const TickType_t xTicksToDelay)
{
    TCB_t *pxTCB = NULL;
    /* 获取当前任务的TCB */
    pxTCB = pxCurrentTCB;
    /* 设置延时时间 */
    pxTCB->xTicksToDelay = xTicksToDelay;
    /* 任务切换 */
    taskYIELD();
}

//-------------------- public functions -------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */
//-------------------- private functions ------------------------------------
/*! \fn			void function(UNSIGNED32 u32Param1)
 *  \brief 		Description of this function
 *  \param 		param1: Description of parameter
 *  \param 		param2: Description of parameter
 *  \exception (None non-reentrant code)
 *  \return 	TRUE: success FALSE: unsuccess
 */


//-----------------------End of file------------------------------------------
/** @} */ /* End of group */

// /**
//   ************************************************************************
//   * @file    main.c
//   * @author  ZYQ
//   * @version V1.0
//   * @date    20200418
//   * @brief   FreeRTOS kernel
//   ************************************************************************
//   * @attention
//   *
//   ************************************************************************
// **/
  
/*
*************************************************************************
*                             多任务实验
*************************************************************************
*/
/*
*************************************************************************
*                             Include
*************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"

/*
*************************************************************************
*                             Macro
*************************************************************************
*/
#define TASK1_STACK_SIZE			128
StackType_t Task1Stack[TASK1_STACK_SIZE];
#define TASK2_STACK_SIZE			128
StackType_t Task2Stack[TASK2_STACK_SIZE];

/*
*************************************************************************
*                             Global variable
*************************************************************************
*/
portCHAR flag1;
portCHAR flag2;

extern List_t pxReadyTasksLists[configMAX_PRIORITIES];

TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;
TCB_t Task1TCB;
TCB_t Task2TCB;

/*
*************************************************************************
*                             Declaration
*************************************************************************
*/
void delay(uint32_t count);
void Task1_Entry(void *p_arg);
void Task2_Entry(void *p_arg);
/*
*************************************************************************
*                             Main
*************************************************************************
*/
int main(void)
{
	/* 初始化与任务相关的列表，如就绪列表 */
	prvInitialiseTaskLists();

	Task1_Handle = xTaskCreateStatic(	(TaskFunction_t)Task1_Entry, //entry
										(char *)"Task1",
										(uint32_t)TASK1_STACK_SIZE,
										(void *)NULL,
										(StackType_t *)Task1Stack,
										(TCB_t *)&Task1TCB	);
	vListInsertEnd(&(pxReadyTasksLists[1]),&(((TCB_t *)(&Task1TCB))->xStateListItem));

	Task2_Handle = xTaskCreateStatic(	(TaskFunction_t)Task2_Entry, //entry
										(char *)"Task2",
										(uint32_t)TASK2_STACK_SIZE,
										(void *)NULL,
										(StackType_t *)Task2Stack,
										(TCB_t *)&Task2TCB	);	
	vListInsertEnd(&(pxReadyTasksLists[2]),&(((TCB_t *)(&Task1TCB))->xStateListItem));

	/* 启动调度器，开始多任务调度，启动成功则不返回 */
	vTaskStartScheduler();

	for(;;);//成功不会到达这里
}
/*
*************************************************************************
*                             Task
*************************************************************************
*/
void delay(uint32_t count)
{
	for(;count!=0;count--);
}
void Task1_Entry(void *p_arg)
{
	for(;;)
	{
#if 0
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
		/* 手动切换 */
		taskYIELD();
#else
        flag1 = 1;
        vTaskDelay(2);//根据systick设置大约20ms
        flag1 = 0;
        vTaskDelay(2);
#endif
	}
}
void Task2_Entry(void *p_arg)
{
	for(;;)
	{
#if 0
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
		/* 手动切换 */
		taskYIELD();
#else
        flag2 = 1;
        vTaskDelay(2);
        flag2 = 0;
        vTaskDelay(2);
#endif
	}
}





// /*
// ************************************************************************
// *                                列表实验
// ************************************************************************
// */
// /*
// *************************************************************************
// *                             include
// *************************************************************************
// */
// #include "list.h"

// /*
// *************************************************************************
// *                             macro
// *************************************************************************
// */
// struct xLIST List_Test;

// struct xLIST_ITEM List_Item1;
// struct xLIST_ITEM List_Item2;
// struct xLIST_ITEM List_Item3;

// /*
// ************************************************************************
// *                                main����
// ************************************************************************
// */
// int main(void)
// {

// 	vListInitialise(&List_Test);

// 	vListInitialiseItem(&List_Item1);
// 	List_Item1.xItemValue = 1;
// 	vListInitialiseItem(&List_Item2);
// 	List_Item2.xItemValue = 2;
// 	vListInitialiseItem(&List_Item3);
// 	List_Item3.xItemValue = 3;

// 	vListInsert(&List_Test,&List_Item1);
// 	vListInsert(&List_Test,&List_Item2);
// 	vListInsert(&List_Test,&List_Item3);

// 	for(;;)
// 	{}
// }
