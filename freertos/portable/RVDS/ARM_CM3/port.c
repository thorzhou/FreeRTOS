/*
*************************************************************************
*                             Include
*************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"
// #include "ARMCM3.H"
/*
*************************************************************************
*                             Macro
*************************************************************************
*/
#define portINITIAL_XPSR (0x01000000)
#define portSTART_ADDRESS_MASK ((StackType_t)0xfffffffeUL)

#define portNVIC_SYSPRI2_REG (*((volatile uint32_t *)0xe000ed20))
#define portNVIC_PENDSV_PRI (((uint32_t)configKERNEL_INTERRUPT_PRIORITY) << 16UL)
#define portNVIC_SYSTICK_PRI (((uint32_t)configKERNEL_INTERRUPT_PRIORITY) << 24UL)


/*
*************************************************************************
*                             Declaration
*************************************************************************
*/
void prvStartFirstTask(void);
void vPortSVCHandler(void);
void xPortPendSVHandler(void);

/*
*************************************************************************
*                             Functions
*************************************************************************
*/
static void prvTaskExitError(void)
{
    /* stop here */
    for (;;);
}

/* 初始化任务栈 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack,
                                    TaskFunction_t pxCode,
                                    void *pvParameters )
{
    /* 异常发生时，自动加载到CPU寄存器的内容,包括8个，R0 R1 R2 R3 R12 R14 R15 XPSR的位24*/
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_XPSR;   //xpsr的位24必须置1，即0x01000000
    pxTopOfStack--;
    *pxTopOfStack = ((StackType_t)pxCode) & portSTART_ADDRESS_MASK;//entry
    pxTopOfStack--;
    *pxTopOfStack = (StackType_t) prvTaskExitError; //返回地址，通常不会反悔，如果返回就跳转到无限循环
    pxTopOfStack -= 5;  //R12 R3 R2 R1 默认初始化为0
    *pxTopOfStack = (StackType_t) pvParameters;

    /* 异常发生时，手动加载到CPU的内容 */
    pxTopOfStack -= 8; //R11 R10 R9 R8 R7 R6 R5 R4
    /* 返回栈顶指针，此时pxTopOfStack指向空闲栈 */
    return pxTopOfStack;
    /*任务第一次运行时，就是从这个栈指针开始手动加载8个字的内容到CPU寄存器：
    R4、R5、R6、R7、R8、R9、R10和R11，当退出异常时，栈中剩下的8个字的内容会自动加载到
    CPU寄存器：R0、R1、R2、R3、R12、R14、R15和xPSR的位24。
    此时PC指针就指向了任务入口地址，从而成功跳转到第一个任务。*/
}

/* 启动调度器 */
BaseType_t xPortStartScheduler(void)
{
    /* 配置PendSV和SysTick的中断优先级为最低 */
    portNVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;

    /* 启动第一个任务，不在返回 */
    prvStartFirstTask();

    /* 不应该运行到这里 */
    return 0;
}

/* 开始第一个任务 */
/* Cortex-M中，内核外设SCB的地址范围为：0xE000ED00 - 0xE000ED3F 
*  0xE000ED08是SCB外设中SCB_VTOR这个寄存器的地址，里面存放的是向量表的其实地址，即MSP的地址
*/
// __asm void prvStartFirstTask(void)
// {
//     PRESERVE8   //当前栈按照8字节对齐，如果都是32位操作则4字节对齐即可，Cortex-M中浮点运算是8字节的
//                 //向量表通常是从内部FLASH的起始地址开始存放0x00000000处存放的就是msp的值
//     ldr r0, =0xE000ED08             //将立即数0xE000ED08加载到r0     目前R0 0xE000ED08
//     ldr r0, [r0]                    //将r0里地址指向的内容加载到r0    目前R0 0x00000000
//     ldr r0, [r0]                    //将r0里地址指向的内容加载到r0    目前R0 0x200008DB
//     /* 设置主堆栈指针msp的值 */
//     msr msp, r0                     //将R0的值存储到MSP，即指向主堆栈的栈顶指针。其实系统启动时这些步骤已经完成，有点多余
//     /* 使能全局中断 */
//     cpsie i                         //CPSID I --- PRIMASK = 1 关中断  CPSIE I --- PRIMASK = 0 开中断
//     cpsie f                         //CPSID F --- FAULTMASK = 1 关异常  CPSIE F --- FAULTMASK = 0 开异常
//     dsb
//     isb
//     /* 调用SVC去启动第一个任务 */
//     svc 0                           //产生系统调用，服务号0表示SVC中断，接下来将会执行SVC中断服务函数
//     nop
//     nop
// }
__asm void prvStartFirstTask(void)
{
    PRESERVE8

    ldr r0, = 0xE000ED08 
    ldr r0, [r0] 
    ldr r0, [r0]

    msr msp,r0

    cpsie i
    cpsie f
    dsb
    isb

    svc 0 
    nop
    nop
}

/* 真正启动第一个任务，不再返回 */
// __asm void vPortSVCHandler(void)
// {
//     extern pxCurrentTCB;

//     PRESERVE8

//     ldr r3, =pxCurrentTCB   //加载pxCurrentTCB的地址到R3
//     ldr r1, [r3]            //加载pxCurrentTCB的地址到R1
//     ldr r0, [r1]            //加载pxCurrentTCB的地址到R0，TCB的第一个成员就是栈顶指针，所以现在R0等于栈顶指针。
//     ldmia r0!, {r4-r11}     //以R0为基地址，将栈中向上增长的8个字节的内容加载到CPU寄存器R4~R11，同时R0自增
//     msr psp, r0             //将新的栈顶指针R0更新到psp，任务执行的时候使用的堆栈指针是psp
//     isb
//     mov r0, #0              //R0清0
//     msr basepri, r0         //设置BASEPRI寄存器值为0，打开所有中断，大于该寄存器值的所有中断被屏蔽，0为缺省值
//     orr r14, #0xd           //当从SVC中断服务退出前，通过向R14寄存器最后4为按位或上0X0D，使得硬件在退出时使用进程堆栈指针psp完成出栈操作并返回后进入任务模式，返回Thumb状态。在SVC中断服务里面，使用的是MSP堆栈指针，是处在ARM状态。
//     bx r14                  //异常返回，这个时候出栈使用的是PSP指针，自动将栈中的剩下内容加载到CPU寄存器：xpsr,pc,r14,r12,r3,r2,r1,r0(任务的形参)同时psp的值也将更新，即指向任务栈的栈顶
// }
__asm void vPortSVCHandler(void)
{
    extern pxCurrentTCB;

    PRESERVE8

    ldr r3, = pxCurrentTCB 
    ldr r1,[r3] 
    ldr r0,[r1] 
    ldmia r0 !,{r4 - r11} 
    msr psp,r0 
    isb
    mov r0, #0 
    msr basepri,r0 
    orr r14,#0xd 
                            

    bx r14 
}

/* PendSV中断服务函数，真正实现任务切换的地方 */
// __asm void xPortPendSVHandler(void)
// {
//     extern pxCurrentTCB;
//     extern vTaskSwitchContext;

//     PRESERVE8

//     mrs r0, psp             //将psp的值存储到r0，当进入PendSV中断服务时，上一个任务的运行环境即：XPSR,PC(ENTRY),R14,R12,R3,R2,R1,R0这些CPU寄存器的值会自动存储到任务的栈中，剩下的R4~R11需要手动保存，勇士PSP会自动更新，（更新之前PSP指向任务栈的栈顶）
//     isb

//     ldr r3, =pxCurrentTCB   //加载pxCurrentTCB的地址到R3
//     ldr r2, [r3]            //加载R3指向的内容到R2
//     stmdb r0!, {r4-r11}     //以R0作为基址（指针先递减，再操作，STMDB的DB表示decrease before），将CPU R4~R11的值存储到任务栈，同时更新R0的值
//     str r0, [r2]            //将R0的值存储到R2指向的内容，R2等于pxCurrentTCB。具体就是将R0的值存储到上一个任务的栈顶指针pxTopOfStack,到此上下文且哈U那种的上文保存就完成了。
//     /*将R3和R14临时压入堆栈（在整个系统中，中断使用的是主堆栈，栈指针使用的是MSP），因为接下来要调用
//     函数vTaskSwitchContext，调用函数时，返回地址自动保存到R14中，所以一旦调用发生，R14的值会被覆盖
//     （PendSV中断服务函数执行完毕后，返回的时候需要根据R14的值来决定返回处理器模式还是任务模式，出栈时
//     使用的是PSP还是MSP），因此需要入栈保护。R3保存的是当前正在运行的任务（准确来说是上文，因为接下来即将
//     要切换到新的任务）的TCB指针(pxCurrentTCB)地址，函数调用后pxCurrentTCB的值会被更新，后面我们还需要
//     通过R3来操作pxCurrentTCB，但是运行函数vTaskSwitchContext时不确定会不会使用R3寄存器作为中间变量，
//     所以为了保险起见，R3也入栈保护起来。*/
//     stmdb sp!, {r3,r14}
//     mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
//     msr basepri, r0         //关中断，进入临界段，因为接下来要更新全局指针pxCurrentTCB的值
//     dsb
//     isb
//     bl vTaskSwitchContext   //task.c，作用是选择优先级最高的任务，然后更新pxCurrentTCB。
//     mov r0, #0
//     msr basepri, r0         //开中断
//     ldmia sp!, {r3,r14}     //从主堆栈中恢复寄存器R3和R14的值，此时sp使用的是MSP

//     ldr r1, [r3]
//     ldr r0, [r1]            //加载下一个任务的TCB
//     ldmia r0!, {r4-r11}
//     msr psp, r0
//     isb
//     bx r14                  //异常发生时，R14中保存异常返回标志，包括返回后进入任务模式还是处理器模式、使用PSP堆栈指针还是MSP堆栈指针。此时的r14等于0xfffffffd，最表示异常返回后进入任务模式，SP以PSP作为堆栈指针出栈，出栈完毕后PSP指向任务栈的栈顶。当调用 bx r14指令后，系统以PSP作为SP指针出栈，把接下来要运行的新任务的任务栈中剩下的内容加载到CPU寄存器：R0（任务形参）、R1、R2、R3、R12、R14（LR）、R15（PC）和xPSR，从而切换到新的任务。
//     nop
// }

__asm void xPortPendSVHandler(void)
{
    extern pxCurrentTCB;
    extern vTaskSwitchContext;

    PRESERVE8
   
    mrs r0, psp 
    isb

    ldr r3,  = pxCurrentTCB 
    ldr r2, [r3] 

    stmdb r0 !,{r4 - r11}
    str r0,[r2] 
    stmdb sp !,{r3, r14} 
    mov r0,#configMAX_SYSCALL_INTERRUPT_PRIORITY
    msr basepri,r0
    dsb
    isb
    bl vTaskSwitchContext
    mov r0,#0
    msr basepri,r0
    ldmia sp !,{r3, r14} 

    ldr r1,[r3] 
    ldr r0, [r1] 
    ldmia r0 !,{r4 - r11} 
    msr psp,r0
    isb
    bx r14 
    nop
}
