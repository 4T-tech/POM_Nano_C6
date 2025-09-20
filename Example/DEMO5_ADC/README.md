# 例程ADC

本例程演示了如何利用ADC的连续采样模式（DMA模式）采集ADC_CHANNEL_1（GPIO1）和ADC_CHANNEL_2（GPIO2）上的模拟输入。

## 代码概述
使用adc_continuous_new_handle进行DMA配置，adc_continuous_config函数进行ADC采样速率、通道参数等配置；使用adc_continuous_read() 实现非阻塞读取ADC采样数据。

## 实验现象
终端可观察到：
EXAMPLE: Unit: ADC_UNIT_1, Channel: 1, Value: xxx（采样值）
EXAMPLE: Unit: ADC_UNIT_1, Channel: 2, Value: yyy（采样值）