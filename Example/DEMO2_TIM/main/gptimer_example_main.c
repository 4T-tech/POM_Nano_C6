#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gptimer.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define GPIO_PIN              GPIO_NUM_18      // 控制GPIO18（根据需求修改）
#define TIMER_INTERVAL_SEC    1               // 2秒触发一次

static gptimer_handle_t gptimer = NULL;

static bool IRAM_ATTR timer_isr(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    static bool level = false;
    gpio_set_level(GPIO_PIN, level);
    level = !level;
    return true;
}

void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_PIN),
        .mode = GPIO_MODE_OUTPUT,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1e6, // 1MHz, 1 tick=1us
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

    uint64_t a = TIMER_INTERVAL_SEC * 1000000;
    gptimer_alarm_config_t alarm_cfg = {
        .alarm_count = a,
        .reload_count = 0,
        .flags.auto_reload_on_alarm = true,
    };
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_cfg));

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_isr,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));

    gptimer_enable(gptimer);
    gptimer_start(gptimer);
}
