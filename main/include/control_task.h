#ifndef CTRL_TASK_H
#define CTRL_TASK_H

#include "driver/gpio.h"
#include "driver/ledc.h"

#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // 4095 (50% brightness), 8191 (100% brightness)
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_FREQ 100
#define LED_CLCK_SRC LEDC_AUTO_CLK
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_OUTPUT_IO GPIO_NUM_2 // define output GPIO

void ledc_init(void);

#endif