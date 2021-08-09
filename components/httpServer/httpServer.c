#include <stdio.h>
#include <esp_log.h>
#include "httpServer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char *TAG_SERVER = "HTTPServer";
ESP_EVENT_DEFINE_BASE(TASK_EVENTS);

/* An HTTP GET handler */
static esp_err_t hello_get_handler(httpd_req_t *req)
{
    const char resp[] = "URI GET Response \n ";
    //API to send a complete HTTP response
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    ESP_LOGI(TAG_SERVER, "Sended Hello Handler Response");
    return ESP_OK;
}

/* URI handler structure for GET /hello */
static const httpd_uri_t hello = {
    .uri = "/hello",
    .method = HTTP_GET,
    .handler = hello_get_handler,
    .user_ctx = NULL};

static esp_err_t echo_post_handler(httpd_req_t *req)
{
    size_t recv_size = MIN(req->content_len, sizeof(inAlpha));
    int ret = httpd_req_recv(req, inAlpha, recv_size);
    inAlpha[recv_size] = '\0';
    if (ret <= 0)
    {
        if (ret == 0)
        {
            ESP_LOGI(TAG_SERVER, "Connection closed by peer");
        }
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            /* In case of timeout we
             * respond with an HTTP 408 (Request Timeout) error */
            httpd_resp_send_408(req);
            ESP_LOGI(TAG_SERVER, "Timeout");
        }
        return ESP_FAIL;
    }
    const char resp[] = "URI POST Response";
    ESP_LOGI(TAG_SERVER, "SUCCESSFUL POST, DATA: %s, SIZE: %d", inAlpha, sizeof(inAlpha));
    ESP_ERROR_CHECK(esp_event_post_to(loop_without_task, TASK_EVENTS, TASK_ITERATION_EVENT, &recv_size, sizeof(recv_size), portMAX_DELAY));
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static const httpd_uri_t echo = {
    .uri = "/echo",
    .method = HTTP_POST,
    .handler = echo_post_handler,
    .user_ctx = NULL};

//Function to start the webserver
httpd_handle_t start_webserver(void)
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    // Start the httpd server
    ESP_LOGI(TAG_SERVER, "Starting server on port: '%d'", config.server_port);

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK)
    {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &echo);
        httpd_register_uri_handler(server, &hello);
        return server;
    }
    /* If server failed to start, handle will be NULL */
    ESP_LOGI(TAG_SERVER, "Error starting server!");
    return NULL;
}

//Function to stop the webserver
void stop_webserver(httpd_handle_t server)
{
    httpd_stop(server);
}
