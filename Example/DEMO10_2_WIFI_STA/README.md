# 例程Wi-Fi STA

本例程展示了如何将esp32c6的WiFi模块设置为STA模式，从而与其他设备进行无线通信。

## 程序概述

wifi_init_sta函数用于WiFi初始化。其中esp_wifi_set_mode函数用于设置WiFi模式（AP或STA），esp_wifi_set_config用于设置WiFi的ID、密码等参数。

event_handler用于响应连接成功或链接失败等事件

### 实验现象
连接成功时终端输出如下：
wifi station: connected to ap SSID:xxx(your WiFi ID) password:xxx(your WiFi password)
