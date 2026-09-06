/* this file contains a NimBLE GATT server
sources: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/get-started/ble-introduction.html
https://github.com/espressif/esp-idf/tree/v6.1/examples/bluetooth/ble_get_started/nimble/NimBLE_GATT_Server


ATT (Attribute Protocol) Layer - defines a basic data structure
called Attribute and data access methods based on a 
client/server architecture. i.e - data is stored on a server 
as attributes, awaiting access by the client

Attribute data structure
    - Handle
    - Type
    - Value
    - Permissions


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
 - uint16_t atr_handle: internal idx no assigned to a characteristic, 
                        can ignore because I used different callbacks 
                        for each characteristic
 - struct ble_gatt_access_ctxt* ctxt: holds the data being sent, informs
                                      you whether it's a r/w operation (ctxt->op)
 - void* arg: generic ptr for passing custom data
 */
static int cmd_char_cb(uint16_t conn_handle, uint16_t atr_handle, 
                       struct ble_gatt_access_ctxt* ctxt, void* arg);
static int state_char_cb(uint16_t conn_handle, uint16_t atr_handle, 
                         struct ble_gatt_access_ctxt* ctxt, void* arg);
static int device_info_cb(uint16_t conn_handle, uint16_t atr_handle, 
                          struct ble_gatt_access_ctxt* ctxt, void* arg);


void ble_server_init(void)
{
    /* define the service UUIDs */

    /* add Characteristics inside the Service */

    /* */
} 

void send_indication(void)
{

}

int gatt_svc_init(void)
{
    /* GATT services table (this is an array of services)*/
    
    static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
        /* device control Service */
        {
            .type = BLE_GATT_SVC_TYPE_PRIMARY, /* primary service*/
            .uuid = BLE_UUID128_DECLARE(DEVICE_SERVICE_UUID),
            .characteristics = 
            (struct ble_gatt_chr_def[]) 
            {
                /* Command Characteristic */
                {
                    .uuid = BLE_UUID128_DECLARE(CMD_CHAR_UUID),
                    .access_cb = cmd_char_cb,
                    .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE,
                },
                /* State Characteristic */
                {
                    .uuid = BLE_UUID128_DECLARE(STATE_CHAR_UUID),
                    .access_cb = state_char_cb,
                    .flags = BLE_GATT_CHR_F_READ
                },
                /* Device Info Characteristic */
                {
                    .uuid = BLE_UUID128_DECLARE(DEVICE_INFO_UUID),
                    .access_cb = device_info_cb,
                    .flags = BLE_GATT_CHR_F_READ
                }, {0} /* NULL-terminator for characteristics array*/
            }
        }

        /* custom service B */
    }
}