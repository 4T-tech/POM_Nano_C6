# 例程Wi-Fi AP

本例程展示了如何将esp32c6的WiFi模块设置为AP模式，从而与其他设备进行无线通信。

## 程序概述

wifi_init_softap函数用于WiFi初始化。其中esp_wifi_set_mode函数用于设置WiFi模式（AP或STA），esp_wifi_set_config用于设置WiFi的ID、密码等参数。

wifi_event_handler用于响应连接wifi与断开wifi的事件

### 实验现象

初始化完成后，终端显示如下：
...
wifi softAP: wifi_init_softap finished. SSID:myssid password:mypassword channel:1
...
有设备连接时：
...
wifi softAP: station d2:22:ca:c7:3f:d1 join, AID=1
...
断开连接时：
...
wifi softAP: station d2:22:ca:c7:3f:d1 leave, AID=1, reason=3
...
