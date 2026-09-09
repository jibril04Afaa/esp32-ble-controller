#ifndef BLE_GAP_H
#define BLE_GAP_H

#include "host/ble_hs.h"

/* this callback handles phones connecting & disconnecting */
int ble_gap_event_cb(struct ble_gap_event* event, void* arg);
 
/* packs the broadcast data & turns on the radio */
void ble_app_advertise(void);

#endif // BLE_GAP_H