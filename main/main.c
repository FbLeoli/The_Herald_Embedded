#include <stdio.h>
#include <nvs_flash.h>
#include <esp_log.h>

#include "esp_gatts_api.h"
#include "httpServer.h"
#include "wifiStation.h"
#include "ble.h"
#include "info.h"
#include "translate.h"

static const char *TAG_MAIN = "Main";

static void application_task(void *args)
{
    while (1)
    {
        ESP_LOGI(TAG_MAIN, "application_task: running application task");
        esp_event_loop_run(loop_without_task, 1);
        vTaskDelay(100);
    }
}

static void task_iteration_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
{
    // Two types of data can be passed in to the event handler: the handler specific data and the event-specific data.
    //
    // The handler specific data (handler_args) is a pointer to the original data, therefore, the user should ensure that
    // the memory location it points to is still valid when the handler executes.
    //
    // The event-specific data (event_data) is a pointer to a deep copy of the original data, and is managed automatically.
    int lenghtphrase = *(int *)event_data;
    char *loop;
    char inMorse[500];
    strcpy(inMorse, alfa2morse(inAlpha));
    if (handler_args == loop_without_task)
    {
        loop = "loop_without_task";
        ESP_LOGI(TAG_MAIN, "STRING: %s", inMorse);
        ESP_ERROR_CHECK(esp_ble_gatts_set_attr_value(handle_table[IDX_CHAR_VAL_A], strlen(inMorse), (const uint8_t *)inMorse));
    }
    ESP_LOGI(TAG_MAIN, "TASK_ITERATION_EVENT: %s", loop);
}

void app_main(void)
{
    esp_event_loop_args_t loop_without_task_args = {
        .queue_size = 50,
        .task_name = NULL // no task will be created
    };

    ESP_ERROR_CHECK(esp_event_loop_create(&loop_without_task_args, &loop_without_task));

    // Register the handler for task iteration event. Notice that the same handler is used for handling event on different loops.
    // The loop handle is provided as an argument in order for this example to display the loop the handler is being run on.
    ESP_ERROR_CHECK(esp_event_handler_instance_register_with(loop_without_task, TASK_EVENTS, TASK_ITERATION_EVENT, task_iteration_handler, loop_without_task, NULL));

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
    ble_init();
    server = start_webserver();

    xTaskCreate(application_task, "application_task", 4096, NULL, uxTaskPriorityGet(NULL), NULL);
}
