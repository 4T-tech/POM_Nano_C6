# 例程PWM

本例程演示了如何使用esp32c6的外设1edc模块产生4kHz、占空比为50%的PWM信号。

## 程序概述
其中ledc_timer_config函数用于配置ledc模块自带定时器的各项参数（如频率等），ledc_channel_config函数用于配置ledc通道的占空比等参数。

初始化后PWM信号的占空比为0，通过ledc_set_duty和ledc_update_duty函数将占空比更新为50%。

## 实验现象
GPIO5上输出4kHz、占空比为50%的PWM信号。