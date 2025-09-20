# 例程Magnetometer

本例程展示了如何借助esp32c6的i2c外设模块与板上的磁力计lis2mdl通信，从而获取磁力计的相关数据。

## 程序概述
i2c_init.c用于i2c的初始化，其中I2C_Init函数配置i2c通信引脚以及从设备ID等参数，并借助i2c_eeprom.c中的i2c_eeprom_init函数完成初始化。

lis2mdl_reg.c为st为开发lis2mdl提供的库文件，包含lis2mdl_device_id_get（获取从设备ID）等初始化函数以及lis2mdl_magnetic_raw_get（获取磁力计数据）等函数。

main函数中，通过给结构体dev_ctx绑定用于i2c通信的函数（i2c_eeprom_write和i2c_eeprom_read）等操作，即可调用lis2mdl_reg库中的相关函数

## 实验现象
终端输出如下：
magnetic: -402, -120, -694
magnetic: -412, -117, -694
···
输出你所测得的数据。