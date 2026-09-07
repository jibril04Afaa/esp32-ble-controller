#include "control_task.h"

/* NOTE TO SELF: use ESP_ERROR_CHECK() & ESP_LOGI() where applicable */

/* official espressif docs for ledc - 
https://github.com/espressif/esp-idf/blob/v6.1/examples/peripherals/ledc/ledc_basic/main/ledc_basic_example_main.c
*/

void ledc_init(void)
{
    /* configure ledc timer for pwm */ 
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER, // 4 timers (0, 1, 2, 3)
        .freq_hz = LEDC_FREQ, // pwm freq unit is hertz (Hz)
        .clk_cfg = LED_CLCK_SRC // clock config
    };

    /* apply the configurations above with an error check */
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    /* apply LEDC PWM channel configs */
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .gpio_num = LEDC_OUTPUT_IO,
        .duty = 0, // set duty to 0
        .hpoint = 0,
    };

    /* apply the configurations above with an error check */
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

