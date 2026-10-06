/*
    This file contains the GAP layer which handles discovery & connections
    Central - Mobile Smartphone
    Peripheral - ESP32(D)

    Sources:
    https://learn.adafruit.com/introduction-to-bluetooth-low-energy/gap
    
*/

#include "gap.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "ble_gatt_svc.h"

int ble_gap_event_cb(struct ble_gap_event* event, void* arg)
{
    switch (event->type)
    {
    /* phone connected successfully */
    case BLE_GAP_EVENT_CONNECT:
        if (event->connect.status == 0)
        {
            printf("BLE device connected! \n");
        }
        else
        {
            printf("Connection failed, restarting advertising... \n");
            ble_app_advertise();
        }
        break;
    
    /* phone disconnected */
    case BLE_GAP_EVENT_DISCONNECT:
        printf("BLE Device disconnected, restarting advertising \n");
        ble_app_advertise();
        break;
    }
    return 0;
}
 
void ble_app_advertise(void)
{
    /* set device name */
    ble_svc_gap_device_name_set("ESP32_Controller");

    /* (MAIN broadcast payload) configure broadcast payload (Over The Air btw) */
    struct ble_hs_adv_fields fields;
    memset(&fields, 0, sizeof(fields)); // zero-initialize fields

    /* General Discoverable Mode & Basic Rate/Enhanced Data Rate */
    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;

    /* attach primary service to UUID. 
       BLE macros from ble_gatt_svc.h */
    ble_uuid128_t svc_uuid = BLE_UUID128_INIT(DEVICE_SERVICE_UUID);
    fields.uuids128 = &svc_uuid;
    fields.num_uuids128 = 1;
    fields.uuids128_is_complete = 1;

    /* push main payload to NimBLE */
    ble_gap_adv_set_fields(&fields);

    /* scan response payload (to fit the device name) */
    struct ble_hs_adv_fields rsp_fields;
    memset(&rsp_fields, 0, sizeof(fields)); // zero-initialize fields

    /* attach name to secondary broadcast */
    rsp_fields.name = (uint8_t*)"ESP32_BLE_Controller";
    rsp_fields.name_len = strlen("ESP32_BLE_Controller");
    rsp_fields.name_is_complete = 1;

    /* push scan response payload to NimBLE */
    ble_gap_adv_set_fields(&rsp_fields);

    /* configure & start the radio */
    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params)); /* zero-initialize advertising parameters */
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND; // allow incoming connections
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN; // allow discovery

    /* official beginning of advertising */
    ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, 
                      NULL, BLE_HS_FOREVER, 
                      &adv_params, ble_gap_event_cb,
                      NULL);

    printf("ESP32 is now advertising... \n");
}