#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <i2c_eeprom.h>
#include "i2c_init.h"
#include "lis2mdl_reg.h"

#define MAG_THRESHOLD_MIN    -500.0f  // 磁力计范围：后续可根据情况自定义
#define MAG_THRESHOLD_MAX     500.0f	//+-500

int16_t data_raw_magnetic[3];
float magnetic_mG[3];
uint8_t mag_whoamI, mag_rst;
stmdev_ctx_t dev_ctx;
static i2c_master_dev_handle_t imu_dev_handle;

int16_t	mag_int16[3]	={0,0,0};

// int32_t mag_platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
// int32_t mag_platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
void MAG_Init(void);
uint8_t get_mag(void);

void app_main(void)
{
    I2C_Init();
    MAG_Init();

    while (1)
    {
        get_mag();
        
        /* Read magnetic field data */
        memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
        lis2mdl_magnetic_raw_get(&dev_ctx, data_raw_magnetic);
        magnetic_mG[0] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[0]);
        magnetic_mG[1] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[1]);
        magnetic_mG[2] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[2]);
        
        mag_int16[0]=(int16_t)(magnetic_mG[0]);
        mag_int16[1]=(int16_t)(magnetic_mG[1]);
        mag_int16[2]=(int16_t)(magnetic_mG[2]);

        vTaskDelay(50);
        printf("magnetic: %d, %d, %d\r\n", mag_int16[0], mag_int16[1], mag_int16[2]);
    }
}

void MAG_Init(void) 
{
  imu_dev_handle = eeprom_handle->i2c_dev;
  dev_ctx.write_reg = i2c_eeprom_write;
  dev_ctx.read_reg = i2c_eeprom_read;
  dev_ctx.mdelay = vTaskDelay;
  dev_ctx.handle = imu_dev_handle;
  
  while (1) {
    lis2mdl_device_id_get(&dev_ctx, &mag_whoamI);
    printf("LIS2MDL_ID=0x%x, whoamI=0x%x\r\n", LIS2MDL_ID, mag_whoamI);
    if (mag_whoamI == LIS2MDL_ID)
        break;
  };
  lis2mdl_reset_set(&dev_ctx, PROPERTY_ENABLE);
  
  do
  {
      lis2mdl_reset_get(&dev_ctx, &mag_rst);
  } while (mag_rst);
  lis2mdl_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  lis2mdl_drdy_on_pin_set(&dev_ctx, PROPERTY_ENABLE);
  lis2mdl_operating_mode_set(&dev_ctx, LIS2MDL_CONTINUOUS_MODE);
  
  lis2mdl_data_rate_set(&dev_ctx, LIS2MDL_ODR_10Hz);
  
  lis2mdl_set_rst_mode_set(&dev_ctx, LIS2MDL_SENS_OFF_CANC_EVERY_ODR);
  
  lis2mdl_offset_temp_comp_set(&dev_ctx, PROPERTY_ENABLE);
  
  lis2mdl_power_mode_set(&dev_ctx, LIS2MDL_HIGH_RESOLUTION);
  
}

uint8_t get_mag(void)
{
  uint8_t reg;
  /* Read output only if new mag value is available */
  lis2mdl_mag_data_ready_get(&dev_ctx, &reg);
  if (reg) {
      /* Read magnetic field data */
      memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
      lis2mdl_magnetic_raw_get(&dev_ctx, data_raw_magnetic);
  }
  return reg;
}