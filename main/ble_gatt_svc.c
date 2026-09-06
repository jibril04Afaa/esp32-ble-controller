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
    /* GATT services table */
    static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
        /* custom service A */

        /* custom service B */
    }
}