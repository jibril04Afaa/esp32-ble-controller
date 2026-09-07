/* this file contains a NimBLE GATT server
sources: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/get-started/ble-introduction.html
https://github.com/espressif/esp-idf/tree/v6.1/examples/bluetooth/ble_get_started/nimble/NimBLE_GATT_Server/main

GATT (Generic Attribute Profile) Layer - defines how devices 
exchange structured data after/around a connection
    - Characteristic
    - Service 
    - Profile (predefined set of services)

    The profile is the top container
        You can have multiple services in a profile
            Each service can have multiple characteristics
    
    GATT server - any device that stores & manages characteristics
    GATT client - any device that accesses the GATT server to retrieve characteristics

*/

#include "ble_gatt_svc.h"
#include <stdint.h>

/* characteristics callbacks
 - uint16_t conn_handle: a unique id representing a specific connection
 - uint16_t atr_handle: internal id no assigned to a characteristic, 
                        can ignore because I used different callbacks 
                        for each characteristic
 - struct ble_gatt_access_ctxt* ctxt: holds the data being sent, informs
                                      you whether it's a r/w operation (ctxt->op)
 - void* arg: generic ptr for passing custom data
 */

 /* phone sends cmds (e.g, LED ON/OFF, change brightness %); this callback intercepts 
 the bytes & passes them to a FreeRTOS queue*/
static int cmd_char_cb(uint16_t conn_handle, uint16_t atr_handle, 
                        struct ble_gatt_access_ctxt* ctxt, void* arg);

/* phone reads the state characteristic & checks
the hardware's live status (e.g, LED ON @ 50%, MOTOR SPINNING @ 25%, etc...)
*/
static int state_char_cb(uint16_t conn_handle, uint16_t atr_handle, 
                         struct ble_gatt_access_ctxt* ctxt, void* arg);

/* phone reads this callback to get static data
(e.g, firmware version, device name, hardware model, etc...)
*/
static int device_info_cb(uint16_t conn_handle, uint16_t atr_handle, 
                          struct ble_gatt_access_ctxt* ctxt, void* arg);

/* define BLE UUID contants */
static const ble_uuid128_t device_svc_uuid = BLE_UUID128_INIT(DEVICE_SERVICE_UUID);
static const ble_uuid128_t cmd_char_uuid = BLE_UUID128_INIT(CMD_CHAR_UUID);
static const ble_uuid128_t state_char_uuid = BLE_UUID128_INIT(STATE_CHAR_UUID);
static const ble_uuid128_t info_char_uuid = BLE_UUID128_INIT(DEVICE_INFO_UUID);


/* GATT services table (this is an array of services)*/
static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    /* device control Service */
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY, /* primary service*/
        .uuid = &device_svc_uuid.u,
        .characteristics = 
        (struct ble_gatt_chr_def[]) 
        {
            /* Command Characteristic */
            {
                .uuid = &cmd_char_uuid.u,
                .access_cb = cmd_char_cb,
                .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE,
            },
            /* State Characteristic */
            {
                .uuid = &state_char_uuid.u,
                .access_cb = state_char_cb,
                .flags = BLE_GATT_CHR_F_READ
            },
            /* Device Info Characteristic */
            {
                .uuid = &info_char_uuid.u,
                .access_cb = device_info_cb,
                .flags = BLE_GATT_CHR_F_READ
            }, {0} /* NULL-terminator for characteristics array*/
        }
    }

    /* custom service B */
};

/* callback implementations */
static int cmd_char_cb(uint16_t conn_handle, uint16_t atr_handle, 
                        struct ble_gatt_access_ctxt* ctxt, void* arg)
{
    // switch (ctxt->op)
    // {
    // /* reading from ESP32 */
    // case BLE_GATT_ACCESS_OP_READ_CHR:
    //     /* code */
    //     break;
    // /* writing to ESP32 */
    // case BLE_GATT_ACCESS_OP_WRITE_CHR:
    //     break;
    
    // default:
    //     break;
    // }

    return 0; /* exit success */
}


static int state_char_cb(uint16_t conn_handle, uint16_t atr_handle, 
                         struct ble_gatt_access_ctxt* ctxt, void* arg)
{
    return 0; /* exit success */

}


static int device_info_cb(uint16_t conn_handle, uint16_t atr_handle, 
                          struct ble_gatt_access_ctxt* ctxt, void* arg)
{
    return 0; /* exit success */

}



void ble_server_init(void)
{
    /* define the service UUIDs */

    /* add Characteristics inside the Service */

    /* */
} 

void send_indication(void)
{

}

/* initiliaze GATT server */
int gatt_svc_init(void)
{
    int rc = 0; /* rc means Return Code*/

    /* GATT service initialization */
    ble_svc_gatt_init();

    /* update GATT services counter */
    rc = ble_gatts_count_cfg(gatt_svr_svcs);
    if (rc != 0)
    {
        return rc;
    }

    /* add GATT services */
    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0)
    {
        return rc;
    }

    return 0; /* return success*/
}