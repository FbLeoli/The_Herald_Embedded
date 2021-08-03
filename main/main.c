#include <stdio.h>
#include <nvs_flash.h>
#include "httpServer.h"
#include "wifiStation.h"
#include "ble.h"
#include "info.h"

void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init(); //initialize the encrypted default NVS partition.
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret); //check if there's some error in nvs

    static httpd_handle_t server = NULL;
    wifi_init_sta();

    //print_chip_info();
    server = start_webserver();
    ble_init();
}
