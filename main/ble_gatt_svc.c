/* this file contains a NimBLE GATT server
sources: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/get-started/ble-introduction.html

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
            .uuid = 0, /* TODO: add uuid */
            .characteristics = 
            (struct ble_gatt_chr_def[]) 
            {
                /* Command Characteristic */
                {
                    .uuid = '',
                    .access_cb = func(),
                    .flags = BLE_GATT_CHR_F_READ
                },
                /* State Characteristic */
                                {
                    .uuid = '',
                    .access_cb = func(),
                    .flags = BLE_GATT_CHR_F_READ
                },
                /* Device Info Characteristic */
                                {
                    .uuid = '',
                    .access_cb = func(),
                    .flags = BLE_GATT_CHR_F_READ
                }, {0} /* NULL-terminator for characteristics array*/
            }
        }

        /* custom service B */
    }
}