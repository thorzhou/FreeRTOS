/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

// #include "stm32f10x.h"
#include "stm32f4xx.h"
// #include "bsp_usart.h"


//针对不同的编译器调用不同的stdint.h文件，MDK中默认__CC_ARM
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

/*
 * 断言：在使用 C 语言编写工程代码时，我们总会对某种假设条件进行检查，断言就是
 * 用于在代码中捕捉这些假设，可以将断言看作是异常处理的一种高级形式。
 * 断言表示为一些布尔表达式，程序员相信在程序中的某个特定表达式值为真。
 * 可以在任何时候启用和禁用断言验证，因此可以在测试时启用断言，而在发布时禁用断言。
 * 同样，程序投入运行后，最终用户在遇到问题时可以重新启用断言。它可以快速发现并定
 * 位软件问题，同时对系统错误进行自动报警。断言可以对在系统中隐藏很深，用其它手段
 * 极难发现的问题可以用断言来进行定位，从而缩短软件问题定位时间，提高系统的可测性。
 * 实际应用时，可根据具体情况灵活地设计断言。这里只是使用宏定义实现了断言的功能，
 * 断言作用很大，特别是在调试的时候，而 FreeRTOS 中使用了很多断言接口 configASSERT，
 * 所以我们需要实现断言，把错误信息打印出来从而在调试中快速定位，打印信息的内容是
 * xxx 文件 xxx 行(__FILE__,__LINE__)。
 */
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

/************************************************************************
 *               FreeRTOS基础配置选项
 *********************************************************************/
/* 置1：RTOS使用抢占式调度器；置0：RTOS使用协作式调度器（时间片）
 * 
 * 注：在多任务管理机制上，OS可以分为抢占式何协作式两种。
 * 协作式OS是任务主动释放CPU后，切换到下一个任务。
 * 任务切换的时机完全取决于正在运行的任务。
 * 抢占式调度：OS总是选择优先级最高的任务进行调度，并且一旦高优先级的任务准备就绪之后，
 * 它就会马上被调度，高优先级的任务抢占了低优先级任务的CPU使用权。
 */
#define configUSE_PREEMPTION					  1

// 1 使能时间片调度（默认使能）
#define configUSE_TIME_SLICING					1		

/* 
 * ͨ某些运行freertos的硬件有两种方法选择下一个要执行的任务：通用方法和特定于硬件的方法
 * 通用方法：软件扫描就绪链表
 *  - configUSE_PORT_OPTIMISED_TASK_SELECTION为0或者硬件不支持这种特殊方法
 *  - 可以用于所有freertos支持的硬件
 *  - 完全用C实现，效率略低于特殊方法
 *  - 不强制要求限制最大可用优先级数目
 * 特殊方法：硬件方式查找
 *  - 必须将configUSE_PORT_OPTIMISED_TASK_SELECTION置1
 *  - 依赖一个或多个特定架构的汇编指令（例如CLZ）
 *  - 比通用方法高效
 *  - 一般强制限定最大可用优先级数目为32
 */
//M3 M4 M7都有CLZ指令，计算第一个1前面有几个0,所以freertos要求优先级最大32
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	        1                       
                                                                        
/* 
 * 置1：使能低功耗tickless模式；置0：保持系统节拍tick中断一直运行
 */
#define configUSE_TICKLESS_IDLE							0   

/*
 * 写入实际的CPU内核时钟频率，也就是CPU指令执行频率，通常称为Fclk
 * Fclk为供给CPU内核的时钟信号，我们所有的cpu主频为x MHz就是指的这个时钟信号，1/Fclk就是时钟周期
 */
#define configCPU_CLOCK_HZ						  (SystemCoreClock)

// RTOS系统节拍中断的频率，即一秒中断的次数，每次中断RTOS都会进行任务调度，中断频率过高会使内核占用过多的CPU时间，降低效率，一般配置为100~1000
#define configTICK_RATE_HZ						  (( TickType_t )1000)

//可使用的最大优先级
#define configMAX_PRIORITIES					  (32)

//空闲任务使用的堆栈大小，512byte
#define configMINIMAL_STACK_SIZE				((unsigned short)128)
  
//任务名字字符串长度，包含'\0'
#define configMAX_TASK_NAME_LEN					(16)

//系统节拍计数器变量数据类型，1表示16位uint16，0表示32位uint32
#define configUSE_16_BIT_TICKS					0                      

//空闲任务放弃CPU使用权给其他同优先级的用户任务，生效条件：启用抢占式，用户任务优先级和空闲任务相等
#define configIDLE_SHOULD_YIELD					1           

//启用消息队列，IPC通信的一种，用于传递消息
#define configUSE_QUEUE_SETS					  1    

// 开启任务通知功能。每个任务有一个32位的通知值，通知是直接向任务发送一个事件，
// 并且接收任务的通知值是可以选择的，任务通过接收到的任务通知值来解除任务的阻塞状态
// （假如因等待该任务通知而进入阻塞状态），相对于队列、二进制信号量、计数信号量或
// 事件组等IPC通信，使用任务通知显然更灵活。官方说明：相比于使用信号量解除任务阻塞，
// 使用任务通知可以快45%（GCC编译器，-o2优化级别），并且使用更少的RAM
#define configUSE_TASK_NOTIFICATIONS    1   

//使用互斥信号量
#define configUSE_MUTEXES						   1    

//使用递归互斥信号量                                    
#define configUSE_RECURSIVE_MUTEXES			1   

//置1时使用计数信号量
#define configUSE_COUNTING_SEMAPHORES		1

/* 设置可以注册的信号量和消息队列个数 */
#define configQUEUE_REGISTRY_SIZE				10                                 
                                                                       
#define configUSE_APPLICATION_TASK_TAG		  0                       
                      

/*****************************************************************
              FreeRTOS与内存申请有关配置选项                                            
*****************************************************************/
//支持动态内存申请
#define configSUPPORT_DYNAMIC_ALLOCATION        1    
//支持静态内存
#define configSUPPORT_STATIC_ALLOCATION					0					
//系统所有总的堆的大小
#define configTOTAL_HEAP_SIZE					((size_t)(36*1024))    


/***************************************************************
             FreeRTOS与钩子函数有关的配置选项
**************************************************************/
/* 置1：使用空闲钩子（Idle Hook类似于回调函数）；置0，忽略空闲钩子
 * 
 * 空闲任务钩子是一个函数，这个函数由用户来实现
 * FreeRTOS规定了函数的名字和参数：void vApplicationIdleHook(void);
 * 这个函数在每个空闲任务周期都会被调用
 * 对于已经删除的RTOS任务，空闲任务可以释放分配给它们的堆栈内存
 * 因此必须保证空闲任务可以被CPU执行
 * 使用空闲钩子函数设置CPU进入省电模式是很常见的
 * 不可以调用会引起空闲任务阻塞的API函数
 */
#define configUSE_IDLE_HOOK						0      

/* 置1：使用时间片钩子（Tick Hook）；置0：忽略时间片钩子 
 * 
 * 时间片钩子是一个函数，这个函数由用户来实现，
 * freertos规定了函数的名字和参数：void vApplicationTickHook(void);
 * 时间片中断可以周期性的调用
 * 函数必须非常短小，不能大量使用堆栈
 * 不能调用以FromISR或FROM_ISR结尾的API函数
 */
#define configUSE_TICK_HOOK						0           

//使用内存申请失败钩子函数
#define configUSE_MALLOC_FAILED_HOOK			0 

/*
 * 大于0时启用堆栈溢出检测功能，如果使用此功能用户必须提供一个栈溢出钩子函数
 * 此值可以为1或2，因为有两种栈溢出检测方法
 */
#define configCHECK_FOR_STACK_OVERFLOW			0   


/********************************************************************
          FreeRTOS与运行时间和任务状态收集有关的配置选项
**********************************************************************/
//启用运行时间统计功能
#define configGENERATE_RUN_TIME_STATS	        0             
//启用可视化跟踪调试
#define configUSE_TRACE_FACILITY				      0    
/* 与宏configUSE_TRACE_FACILITY同时为1时会编译下面3个函数
 * prvWriteNameToBuffer()
 * vTaskList(),
 * vTaskGetRunTimeStats()
*/
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       
                                                                        
                                                                        
/********************************************************************
                FreeRTOS与协程有关的配置选项
*********************************************************************/
//启用协程以后必须添加文件croutine.c，一般不使用因为freertos不再支持
#define configUSE_CO_ROUTINES 			          0                 
//协程的有效优先级数目
#define configMAX_CO_ROUTINE_PRIORITIES       ( 2 )                   


/***********************************************************************
                FreeRTOS与软件定时器有关的配置选项
**********************************************************************/
//启用软件定时器
#define configUSE_TIMERS				            1                            
//软件定时器优先级，配置为最高优先级
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        
//软件定时器队列长度
#define configTIMER_QUEUE_LENGTH		        10                               
//软件定时器任务堆栈大小
#define configTIMER_TASK_STACK_DEPTH	      (configMINIMAL_STACK_SIZE*2)    

/************************************************************
            FreeRTOS可选函数配置选项                                                   
************************************************************/
#define INCLUDE_xTaskGetSchedulerState       1                          //使能使用xTaskGetSchedulerState()
#define INCLUDE_vTaskPrioritySet		         1                      //使能使用vTaskPrioritySet()
#define INCLUDE_uxTaskPriorityGet		         1                      //使能使用uxTaskPriorityGet()
#define INCLUDE_vTaskDelete				           1                    //使能使用vTaskDelete()
#define INCLUDE_vTaskCleanUpResources	       1
#define INCLUDE_vTaskSuspend			           1
#define INCLUDE_vTaskDelayUntil			         1
#define INCLUDE_vTaskDelay				           1
#define INCLUDE_eTaskGetState			           1
#define INCLUDE_xTimerPendFunctionCall	     0
//#define INCLUDE_xTaskGetCurrentTaskHandle       1
//#define INCLUDE_uxTaskGetStackHighWaterMark     0
//#define INCLUDE_xTaskGetIdleTaskHandle          0


/******************************************************************
            FreeRTOS与中断有关的配置选项                                             
******************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif
//中断最低优先级
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15     

//系统可管理的最高中断优先级, basepri的值
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5 

#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	/* 240 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )


/****************************************************************
            FreeRTOS与中断服务函数有关的配置选项                       
****************************************************************/
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler


/* 以下为使用Precepio Tracealyzer需要的东西，不需要时将configUSE_TRACE_FACILITY定义为0 */
#if ( configUSE_TRACE_FACILITY == 1 )
#include "trcRecorder.h"
#define INCLUDE_xTaskGetCurrentTaskHandle               1   // 启用一个可选函数（该函数被Trace源码使用，默认该值为0表示不用）
#endif


#endif /* FREERTOS_CONFIG_H */
