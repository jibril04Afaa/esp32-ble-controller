#ifndef BLE_GAP_H
#define BLE_GAP_H

#include "host/ble_hs.h"

/* this callback handles phones connecting & disconnecting */
int ble_gap_event_cb(struct ble_gap_event* event, void* arg);
 
/* formats the data payload the ESP32 broadcasts 
   through the air, & configures the physical radio hardware 
   to transmit it.
    
   packs the broadcast data & turns on the radio
   i.e. the ESP32 broadcasts its presence as a peripheral */
void ble_app_advertise(void);

#endif // BLE_GAP_H