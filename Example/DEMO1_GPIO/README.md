# 例程: GPIO

该例程展示了如何配置esp32c6的GPIO，以及如何控制GPIO引脚的电平每1s翻转1次。

## GPIO功能

| GPIO                         | Direction |
| ---------------------------- | --------- |
| CONFIG_GPIO_OUTPUT_0(GPIO18) | output    |
| CONFIG_GPIO_OUTPUT_1(GPIO19) | output    |

## 实验现象
1. GPIO18和GPIO19的电平以每秒一次的速率翻转。
2. 终端输出如下：
I (317) gpio: GPIO[18]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (327) gpio: GPIO[19]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
cnt: 0
cnt: 1
cnt: 2
```