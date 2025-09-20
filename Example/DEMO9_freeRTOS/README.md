# 例程FreeRTOS

本例程展示了如何使用freertos操作系统并行地处理两个任务（GPIO电平翻转与终端打印任务）。

## 程序概述
xTaskCreate函数用于创建一条独立线程，并为该线程分配任务

## 实验现象
GPIO电平以每秒两次的速率翻转的同时，终端输出如下：
...
I (751) ESP32C6_TASKS: GPIO toggled, cnt = 1
I (861) ESP32C6_TASKS: hello!
I (1061) ESP32C6_TASKS: hello!
I (1251) ESP32C6_TASKS: GPIO toggled, cnt = 2
I (1261) ESP32C6_TASKS: hello!
I (1461) ESP32C6_TASKS: hello!
I (1661) ESP32C6_TASKS: hello!
I (1751) ESP32C6_TASKS: GPIO toggled, cnt = 3
I (1861) ESP32C6_TASKS: hello!
I (2061) ESP32C6_TASKS: hello!
I (2251) ESP32C6_TASKS: GPIO toggled, cnt = 4
I (2261) ESP32C6_TASKS: hello!
I (2461) ESP32C6_TASKS: hello!
I (2661) ESP32C6_TASKS: hello!
...