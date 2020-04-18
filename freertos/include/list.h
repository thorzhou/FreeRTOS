#ifndef LIST_H
#define LIST_H

#include "FreeRTOS.h"

/* 节点结构体定义 */
struct xLIST_ITEM
{
    TickType_t xItemValue; //辅助值，帮助节点升序排列,数值越大，顺序越靠后
    struct xLIST_ITEM *pxNext;
    struct xLIST_ITEM *pxPrevious;
    void *pvOwner;     //指向拥有该节点的内核对象，TCB
    void *pvContainer; //指向该节点所在的链表
};
typedef struct xLIST_ITEM ListItem_t;

/*链表精简节点结构体定义*/
struct xMINI_LIST_ITEM
{
    TickType_t xItemValue;  //辅助值，帮助节点升序排列
    struct xLIST_ITEM *pxNext;/*链表下一个节点*/
    struct xLIST_ITEM *pxPrevious;/*链表前一个节点*/
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;/*精简节点数据类型重定义*/

/*链表根节点数据结构定义*/
typedef struct xLIST
{
    UBaseType_t uxNumberOfItems; //链表节点计数器
    ListItem_t *pxIndex;        //链表节点索引指针
    MiniListItem_t xListEnd;    //链表最后一个节点
}List_t;

/*
************************************************************************
*                           macro
*                           节点带参宏小函数
************************************************************************
*/
/* 初始化节点的拥有者 */
#define listSET_LIST_ITEM_OWNER(pxListItem, pxOwner)\
            ((pxListItem)->pvOwner = (void *)(pxOwner))
/* 获取节点的拥有者 */
#define listGET_LIST_ITEM_OWNER(pxListItem)\
            ((pxListItem)->pvOwner)
/* 初始化节点排序辅助值 */
#define listSET_ITEM_VALUE(pxListItem,xValue)\
            ((pxListItem)->xItemValue = (xValue))
/* 获取节点排序辅助值 */
#define listGET_LIST_ITEM_VALUE(pxListItem)\
            ((pxListItem)->xItemValue)
/* 获取链表入口的辅助排序值 */
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList)\
            (((pxList)->xListEnd).pxNext->xItemValue)
/* 获取链表的入口节点 */
#define listGET_HEAD_ENTRY(pxList) (((pxList)->xListEnd).pxNext)
/* 获取节点的下一个节点 */
#define listGET_NEXT(pxListItem) ((pxListItem)->pxNext)
/* 获取链表的最后一个节点 */
#define listGET_END_MARKER(pxList)\
            ((ListItem_t const *)(&((pxList)->xListEnd)))
/* 判断链表是否为空 */
#define listLIST_IS_EMPTY(pxList) ((BaseType_t)((pxList)->uxNumberOfItems == (UBaseType_t)0))
/* 获取链表的节点数 */
#define listCURRENT_LIST_LENGTH(pxList) ((pxList)->uxNumberOfItems)
/* 获取链表第一个节点的OWNER，TCB */    
#define listGET_OWNER_OF_NEXT_ENTRY(pxTCB,pxList)                                   \
{                                                                                   \
    List_t * const pxConstList = (pxList);                                          \
    /* 节点索引指向链表的下一个节点 */                                                \
    (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;                        \
    /* 这里应该是因为ListEnd是虚的，没有Owner */                                      \
    if((void *)(pxConstList)->pxIndex == (void *)&((pxConstList)->xListEnd))        \
    {                                                                               \
        (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;                    \
    }                                                                               \
    /* 获取节点的OWNER */                                                            \
    (pxTCB) = (pxConstList)->pxIndex->pvOwner;                                      \
}
#define listGET_OWNER_OF_HEAD_ENTRY(pxList) ((&((pxList)->xListEnd))->pxNext->pvOwner)

/*
************************************************************************
*                           export functions
************************************************************************
*/
void vListInitialiseItem(ListItem_t *const pxItem);
void vListInitialise(List_t *const pxList);
void vListInsertEnd(List_t *const pxList, ListItem_t *const pxNewListItem);
void vListInsert(List_t *const pxList, ListItem_t *const pxNewListItem);
UBaseType_t uxListRemove(ListItem_t *const pxItemToRemove);

#endif /*List_H*/
