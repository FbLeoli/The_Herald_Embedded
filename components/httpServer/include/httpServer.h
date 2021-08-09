#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <esp_http_server.h>
#include "esp_event.h"
#include "esp_timer.h"
httpd_handle_t start_webserver(void);

void stop_webserver(httpd_handle_t server);
ESP_EVENT_DECLARE_BASE(TASK_EVENTS);
esp_event_loop_handle_t loop_without_task;
char inAlpha[100];

enum
{
    TASK_ITERATION_EVENT // raised during an iteration of the loop within the task
};

#endif