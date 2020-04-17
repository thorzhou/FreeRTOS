# -*- coding:UTF-8 -*-
import os,sys

dic = {
    r'.\User\main.c':'主程序入口',
    r'.\freertos\list.c':'列表操作',
    r'.\freertos\include\list.h':'列表操作声明文件'
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