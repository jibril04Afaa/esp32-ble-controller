#include "control_task.h"

#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"

#include "ble_gatt_svc.h"
#include "gap.h"
#include "control_task.h"


/* global queue variable */
extern QueueHandle_t Queue_CMD;

/* full architecture diagram - https://excalidraw.com/#json=-7hud_uCYIXXNvqZRTbej,gwC8Xy7wQsYI_e4KHSQnGw*/


/* this FreeRTOS task keeps the bluetooth stack running in the background */
void ble_host_task(void* param)
{
    nimble_port_run();
    nimble_port_freertos_deinit();
}

/* NimBLE requires a callback to know when 
the stack is fully synced and ready to transmit */
void ble_on_sync(void)
{
    /* trigger custom advertising function 
    once the radio is online */
    ble_app_advertise();
}


void app_main(void)
{
    /* initialize NVS flash */
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* initialize the NimBLE port */
    nimble_port_init();

    /* initialize custom GATT server */
    gatt_svc_init();

    /* tell NimBLE which function to run */
    ble_hs_cfg.sync_cb = ble_on_sync;

    /* initialize FreeRTOS Queue to hold up to 10 cmds (1 byte each)*/
    Queue_CMD = xQueueCreate(10, sizeof(uint8_t));

    if (Queue_CMD == NULL)
    {
        printf("Failed to create Queue_CMD. \n");
    }

    xTaskCreate(hardware_control_task, "HW_CONTROL_TASK", 
                2048, NULL, 1, NULL);

    /* hand control over to the NimBLE FreeRTOS background task */
    nimble_port_freertos_init(ble_host_task);
}
    