#include "i2c_init.h"

i2c_eeprom_handle_t eeprom_handle;

void disp_buf(uint8_t *buf, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void I2C_Init()
{
    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = PORT_NUMBER,
        .scl_io_num = SCL_IO_PIN,
        .sda_io_num = SDA_IO_PIN,
        .glitch_ignore_cnt = 7,
    };
    i2c_master_bus_handle_t bus_handle;

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, &bus_handle));

    i2c_eeprom_config_t eeprom_config = {
        .eeprom_device.scl_speed_hz = MASTER_FREQUENCY,
        .eeprom_device.device_address = MAG_ADDR,
        .addr_wordlen = I2C_ADDR_BIT_LEN_7,
        .write_time_ms = 10,
    };

    ESP_ERROR_CHECK(i2c_eeprom_init(bus_handle, &eeprom_config, &eeprom_handle));
// I2C_ADDR_BIT_LEN_7
}