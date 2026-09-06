#ifndef BLE_GATT_SVC_H
#define BLE_GATT_SVC_H

#include <stdint.h>

/* NimBLE GATT APIs */
#include "host/ble_gatt.h"
#include "services/gatt/ble_svc_gatt.h"

/* function definitions */
void ble_server_init(void); 
void send_indication(void);
int gatt_svc_init(void);

#endif // BLE_GATT_SVC_H