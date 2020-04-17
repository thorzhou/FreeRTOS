
/*
*   struct
*/
/* 节点结构体定义 */
struct xLIST_ITEM
{
    TickType_t xItemValue;          //辅助值，帮助节点升序排列
    struct xLIST_ITEM *pxNext; 
    struct xLIST_ITEM *pxPrevious;
    void *pvOwner;                  //指向拥有该节点的内核对象，TCB
    void *pvContainer;              //指向该节点所在的链表
};
typedef struct xLIST_ITEM ListItem_t;
