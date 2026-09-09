idf_component_register(SRCS "esp32-ble-controller.c" "src/ble_gatt_svc.c" "src/gap.c" "src/control_task.c"
                       INCLUDE_DIRS "include" "."
                       REQUIRES nvs_flash bt esp_driver_ledc)