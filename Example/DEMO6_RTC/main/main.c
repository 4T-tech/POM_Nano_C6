#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "time.h"
#include "sys/time.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RTC_CLK_CAL_SECONDS  3600  // RTC时钟校准周期（秒）

void init_rtc() {
    // 1. 配置RTC时钟源（默认已启用内部150kHz RC振荡器）
    // 2. 校准RTC时钟（可选）
    // 3. 设置初始时间（UNIX时间戳）
    struct tm timeinfo = {
        .tm_year = 125,  // 2025-1900
        .tm_mon = 6,     // 7月
        .tm_mday = 10,
        .tm_hour = 12,
        .tm_min = 0,
        .tm_sec = 0
    };
    time_t t = mktime(&timeinfo);
    struct timeval now = {.tv_sec = t};
    settimeofday(&now, NULL);
}

void app_main() {
    init_rtc();

    while (1) {
        // 4. 获取当前RTC时间
        struct tm timeinfo;
        time_t now;
        time(&now);
        localtime_r(&now, &timeinfo);
        printf("RTC Time: %04d-%02d-%02d %02d:%02d:%02d\n",
               timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
               timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}