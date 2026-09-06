idf_component_register(SRCS "ble_gatt_svc.c" "esp32-ble-controller.c" "control_task.c"
                       INCLUDE_DIRS "include" "."
                       REQUIRES nvs_flash bt)