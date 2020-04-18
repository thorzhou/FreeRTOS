# -*- coding:UTF-8 -*-
import os,sys

dic = {
    r'.\User\main.c':'主程序入口',
    r'.\freertos\list.c':'列表操作',
    r'.\freertos\include\list.h':'列表操作声明文件',
    r'.\freertos\include\portmacro.h':'不同平台下变量类型定义',
    r'.\freertos\include\FreeRTOS.h':'平台相关数据类型包含文件',
    r'.\freertos\include\FreeRTOSConfig.h':'系统时钟位数定义',
    r'.\freertos\include\portable.h':'包含portmacro.h',
    r'.\freertos\list.c':'节点链表初始化'
}

def Query(filePath):
    print(filePath+':',dic[filePath])

def Entry():
    i = len(sys.argv)
    if i == 1:
        print("usage: \n\tThis script must be run under the dir 'FreeRTOS'.\n\tpython DocumentDescription.py .\...")
        exit()
    elif i == 2:
        Query(sys.argv[1])

if __name__ == "__main__":
    Entry()