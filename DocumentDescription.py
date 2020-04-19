# -*- coding:UTF-8 -*-
import os,sys

dic = {
    'main.c':'主程序入口',
    'list.c':'节点链表操作',
    'list.h':'列表操作声明文件',
    'portmacro.h':'不同平台下变量类型定义，将标准C类型重定义一个名字，任务切换实现',
    'FreeRTOS.h':'平台相关数据类型包含文件',
    'FreeRTOSConfig.h':'系统相关定义，时钟，任务，优先级，中断函数声明等',
    'portable.h':'包含portmacro.h',
    'projdefs.h':'重定义函数指针，操作成功失败的声明',
    'task.h':'创建任务的函数声明',
    'task.c':'任务创建相关函数',
    'port.c':'任务创建，加入就绪列表等操作函数'
}

def Query(filePath):
    print(filePath+':',dic[filePath])

def Entry():
    i = len(sys.argv)
    if i == 1:
        print("usage: \n\tThis script must be run under the dir 'FreeRTOS'.\n\tpython DocumentDescription.py .\\...")
        exit()
    elif i == 2:
        Query(sys.argv[1])

if __name__ == "__main__":
    Entry()