#include "control_task.h"
#include "freertos/FreeRTOS.h"

/* NOTE TO SELF: use ESP_ERROR_CHECK() & ESP_LOGI() where applicable */

/* official espressif docs for ledc - 
https://github.com/espressif/esp-idf/blob/v6.1/examples/peripherals/ledc/ledc_basic/main/ledc_basic_example_main.c
*/

/* global queue variable */
QueueHandle_t Queue_CMD;

// GIOP 2 


void hardware_control_task(void* pvParameters)
{
    uint8_t received_cmd;

    /* initialize hardware drivers (ledc pwm in this case) */
    ledc_init();
    printf("Hardware control task started, awaiting commands... \n");

    /* infinite FreeRTOS execution loop */
    for(;;)
    {
        /* block task efficiently until data arrives */
        if (xQueueReceive(Queue_CMD, &received_cmd, portMAX_DELAY) == pdTRUE)
        {
            printf("Hardware task executing command: 0x%02X\n", received_cmd);

            /* route command to physical hardware */
            switch (received_cmd)
            {
            case 0x01: // 0x01 - 1 (base10)
                printf("Executing: Device ON \n");
                /* 255 is 100% duty cycle */
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 255);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
                break;
            case 0x32: // 0x32 - 50 (base10)
                /* 0 is 0% duty cycle */
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
                break;
            
            default:
                printf("Unknown commmand received. \n");
                break;
            }
        }
    }
}


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

