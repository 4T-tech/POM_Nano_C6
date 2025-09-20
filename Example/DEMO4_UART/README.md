# 例程UART

本例程演示了如何配置串口的各项参数并使能串口，从而利用串口收发数据

## 程序概述
利用uart_param_config函数配置串口的各项参数、uart_set_pin函数配置串口引脚，并使用uart_read_bytes和uart_write_bytes函数接收并发送数据

## 实验现象
1. 利用串口助手向串口发送数据后，可以在串口助手上观察到其返回的数据。

2. 串口接收到数据时，终端可观察到：
UART TEST: Recv str: xxx（所发送的数据）