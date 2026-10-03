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

    /* configure broadcast payload */
}