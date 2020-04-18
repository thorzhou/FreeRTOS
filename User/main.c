/**
  ************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   ��FreeRTOS�ں�ʵ����Ӧ�ÿ���ʵսָ�ϡ��鼮����
  *           �б����б���
  ************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 ϵ�� ������
  * 
  * ����    :www.embedfire.com  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ************************************************************************
  */
  
/*
*************************************************************************
*                             include
*************************************************************************
*/
#include "list.h"

struct xLIST List_Test;

struct xLIST_ITEM List_Item1;
struct xLIST_ITEM List_Item2;
struct xLIST_ITEM List_Item3;

/*
************************************************************************
*                                main����
************************************************************************
*/
int main(void)
{

	vListInitalise(&List_Test);

	vListInitialiseItem(&List_Item1);
	List_Item1.xItemValue = 1;
	vListInitialiseItem(&List_Item2);
	List_Item2.xItemValue = 2;
	vListInitialiseItem(&List_Item3);
	List_Item3.xItemValue = 3;

	vListInsert(&List_Test,&List_Item1);
	vListInsert(&List_Test,&List_Item2);
	vListInsert(&List_Test,&List_Item3);
	
	for(;;)
	{}
}
