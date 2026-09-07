#ifndef BLE_GATT_SVC_H
#define BLE_GATT_SVC_H

#include <stdint.h>

/* NimBLE GATT APIs */
#include "host/ble_gatt.h"
#include "host/ble_uuid.h"
#include "services/gatt/ble_svc_gatt.h"

/* UUID procedure:
   NimBLE requires the 16 bytes to be in reverse order (Little-Endian).
   generated random uuids with https://www.uuidgenerator.net/.
   break UUID into hex bytes (pairs), and reverse order
 */

/* main service
   generated UUID : d4aba09e-4642-40c3-9b2d-199bac62d602 */
#define DEVICE_SERVICE_UUID \
    0x02, 0xd6, 0x62, 0xac, 0x9b, 0x19, 0x2d, 0x9b, \
    0xc3, 0x40, 0x42, 0x46, 0x9e, 0xa0, 0xab, 0xd4

/* command characteristic
   generated UUID: ab266966-0189-41c5-bdcb-13f98c98ae1d */
#define CMD_CHAR_UUID \
    0x1d, 0xae, 0x98, 0x8c, 0xf9, 0x13, 0xcb, 0xbd, \
    0xc5, 0x41, 0x89, 0x01, 0x66, 0x69, 0x26, 0xab

/* state characteristic
   generated UUID: 03258638-919d-418a-a0c4-d497bb625895 */
#define STATE_CHAR_UUID \
    0x95, 0x58, 0x62, 0xbb, 0x97, 0xd4, 0xc4, 0xa0, \
    0x8a, 0x41, 0x9d, 0x91, 0x38, 0x86, 0x25, 0x03

/* device info characteristic
   generated UUID: 64ffa038-f557-4fa6-b532-56f2749ab2c4 */
#define DEVICE_INFO_UUID \
    0xc4, 0xb2, 0x9a, 0x74, 0xf2, 0x56, 0x32, 0xb5, \
    0xa6, 0x4f, 0x57, 0xf5, 0x38, 0xa0, 0xff, 0x64

/* function definitions */
void ble_server_init(void); 
void send_indication(void);
int gatt_svc_init(void);


#endif // BLE_GATT_SVC_H