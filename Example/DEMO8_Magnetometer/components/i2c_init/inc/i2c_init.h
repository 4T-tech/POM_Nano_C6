#ifndef I2C_INIT_H
#define I2C_INIT_H

#include <stdio.h>
#include <stdint.h>
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "i2c_eeprom.h"
#include "lis2mdl_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCL_IO_PIN 7
#define SDA_IO_PIN 6
#define MASTER_FREQUENCY 400000
#define PORT_NUMBER -1
#define LENGTH 48
#define MAG_ADDR 0x1eU
// #define LIS2MDL_I2C_ADD_H 0x3DU

extern i2c_eeprom_handle_t eeprom_handle;

void disp_buf(uint8_t *buf, int len);
void I2C_Init();

#ifdef __cplusplus
}
#endif
#endif