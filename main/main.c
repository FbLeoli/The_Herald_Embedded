#include <stdio.h>
#include "info.h"
#include <httpServer.h>
#include <esp_wifi.h> 

void app_main(void)
{
    static httpd_handle_t server = NULL;


    // print_chip_info();
    server = start_webserver();
}
