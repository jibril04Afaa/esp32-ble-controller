#include "control_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void)
{
    /* call helper function */
    ledc_init();

    /* test brightness levels */
    for (;;)
    {
        printf("LED OFF: (0%%)\n");
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0); // write the duty to memory
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL); // update and apply to the physical pin
        vTaskDelay(pdMS_TO_TICKS(2000)); // add 2 second delay

        printf("LED DIM: (25%%)\n");
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 2048);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        vTaskDelay(pdMS_TO_TICKS(2000)); // add 2 second delay

        printf("LED MEDIUM: (50%%)\n");
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 4095);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        vTaskDelay(pdMS_TO_TICKS(2000)); // add 2 second delay

        // printf("LED OFF: (75%%)\n");
        // ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
        // ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        // vTaskDelay(pdMS_TO_TICKS(2000)); // add 2 second delay

        printf("LED MAX: (100%%)\n");
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 8191);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        vTaskDelay(pdMS_TO_TICKS(2000)); // add 2 second delay

    }
}
 