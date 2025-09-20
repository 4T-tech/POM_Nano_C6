#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <i2c_eeprom.h>
#include "i2c_init.h"
#include "lsm6dso_reg.h"


#define ACCEL_THRESHOLD_MIN   -2500.0f  // 加速度范围：后续可根据情况自定义
#define ACCEL_THRESHOLD_MAX   	2500.0f  //	+-2500
#define GYRO_THRESHOLD_MIN    -2200.0f  // 陀螺仪范围：后续可根据情况自定义
#define GYRO_THRESHOLD_MAX     2200.0f	 // +-2200

static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
// static int16_t data_raw_temperature;
static float acceleration_mg[3];
static float angular_rate_mdps[3];
// static float temperature_degC;
static uint8_t whoamI, rst;
static stmdev_ctx_t dev_ctx;
static i2c_master_dev_handle_t imu_dev_handle;

int16_t	acc_int16[3]	={0,0,0};
int16_t	gyr_int16[3]	={0,0,0};	

// static int32_t imu_platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
// static int32_t imu_platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
void IMU_Init();
uint8_t get_xl();
uint8_t get_gy();

void app_main(void)
{
    I2C_Init();
    IMU_Init();

    while (1)
    {
        get_xl();
        get_gy();
        
        memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
        lsm6dso_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
        acceleration_mg[0] =
        lsm6dso_from_fs2_to_mg(data_raw_acceleration[0]);
        acceleration_mg[1] =
        lsm6dso_from_fs2_to_mg(data_raw_acceleration[1]);
        acceleration_mg[2] =
        lsm6dso_from_fs2_to_mg(data_raw_acceleration[2]);
        
        acc_int16[0]=(int16_t)(acceleration_mg[0]);
        acc_int16[1]=(int16_t)(acceleration_mg[1]);
        acc_int16[2]=(int16_t)(acceleration_mg[2]);
        
        memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
        lsm6dso_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
        angular_rate_mdps[0] =
        lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate[0]);
        angular_rate_mdps[1] =
        lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate[1]);
        angular_rate_mdps[2] =
        lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate[2]);
        
        gyr_int16[0]=(int16_t)(angular_rate_mdps[0]/1000);
        gyr_int16[1]=(int16_t)(angular_rate_mdps[1]/1000);
        gyr_int16[2]=(int16_t)(angular_rate_mdps[2]/1000);
        
        vTaskDelay(50);

        printf("acceleration: %d, %d, %d\r\n", acc_int16[0], acc_int16[1], acc_int16[2]);
        printf("angular_rate: %d, %d, %d\r\n", gyr_int16[0], gyr_int16[1], gyr_int16[2]);
    }
}

void IMU_Init()
{
    imu_dev_handle = eeprom_handle->i2c_dev;
    dev_ctx.write_reg = i2c_eeprom_write;
    dev_ctx.read_reg = i2c_eeprom_read;
    dev_ctx.mdelay = vTaskDelay;
    dev_ctx.handle = imu_dev_handle;
    while (1)
    {
        lsm6dso_device_id_get(&dev_ctx, &whoamI);
        printf("LSM6DSO_ID=0x%x,whoamI=0x%x\r\n",LSM6DSO_ID,whoamI);
        if (whoamI == LSM6DSO_ID)
        break;
    };
    lsm6dso_reset_set(&dev_ctx, PROPERTY_ENABLE);
    do {
        lsm6dso_reset_get(&dev_ctx, &rst);
    } while (rst);
    lsm6dso_i3c_disable_set(&dev_ctx, LSM6DSO_I3C_DISABLE);
    lsm6dso_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
    lsm6dso_xl_data_rate_set(&dev_ctx, LSM6DSO_XL_ODR_12Hz5);
    lsm6dso_gy_data_rate_set(&dev_ctx, LSM6DSO_GY_ODR_12Hz5);
    lsm6dso_xl_full_scale_set(&dev_ctx, LSM6DSO_2g);
    lsm6dso_gy_full_scale_set(&dev_ctx, LSM6DSO_2000dps);
    lsm6dso_xl_hp_path_on_out_set(&dev_ctx, LSM6DSO_LP_ODR_DIV_100);
    lsm6dso_xl_filter_lp2_set(&dev_ctx, PROPERTY_ENABLE);
}

uint8_t get_xl()
{
  uint8_t reg;
  /* Read output only if new xl value is available */
  lsm6dso_xl_flag_data_ready_get(&dev_ctx, &reg);
  if (reg) 
  {
    /* Read acceleration field data */
    memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
    lsm6dso_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
  }
  return reg;
}

uint8_t get_gy()
{
  uint8_t reg;
  lsm6dso_gy_flag_data_ready_get(&dev_ctx, &reg);
  if (reg) 
  {
    /* Read angular rate field data */
    memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
    lsm6dso_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
  }
  return reg;
}