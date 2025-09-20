#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define GPIO_PIN    18
#define GPIO_OUTPUT_PIN_SEL  1ULL<<GPIO_PIN

#define TAG "ESP32C6_TASKS"

void GPIO_Init(void)
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}

// GPIO控制任务
void gpio_task(void *pvParameters) {
    // gpio_reset_pin(GPIO_PIN);
    int cnt = 0;
    while (1) {
        gpio_set_level(GPIO_PIN, cnt % 2);  // 电平翻转
        ESP_LOGI(TAG, "GPIO toggled, cnt = %d", cnt);
        cnt++;
        vTaskDelay(pdMS_TO_TICKS(500));  // 延迟500ms
    }
}

// 打印任务
void print_task(void *pvParameters) {
    while (1) {
        ESP_LOGI(TAG, "hello!");
        vTaskDelay(pdMS_TO_TICKS(200));  // 延迟200ms
    }
}

void app_main() {
    GPIO_Init();
    // 创建GPIO控制任务（优先级1，栈大小2048字节）
    xTaskCreate(gpio_task, "gpio_task", 2048, NULL, 1, NULL);
    // 创建打印任务（优先级1，栈大小2048字节）
    xTaskCreate(print_task, "print_task", 2048, NULL, 1, NULL);
}