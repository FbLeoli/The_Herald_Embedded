/* Simple HTTP server
   Creates GET and POST handlers for the web server */
#include <stdio.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "protocol_examples_common.h"
#include "esp_tls_crypto.h"
#include <httpServer.h>

static const char *TAG == "httpServer";

#if CONFIG_BASIC_AUTH

typedef struct
{
    char *username;
    char *password;
} basic_auth_info_t; //Information to authenticate

#define HTTPD_401 "401 UNAUTHORIZED" // HTTP 401 RESPONSE

static char *http_auth_basic(const char *username, const char *password)
{
    int out;
    char *user_info = NULL;
    char *digest = NULL;
    size_t n = 0;

    asprintf(&user_info, "%s:%s", username, password); //print username:password in the string user_info
    if (!user_info)
    { //if there is no space to alloc in memory (part of asprintf)
        ESP_LOGE(TAG, "No enough memory for user information");
        return null;
    }
    esp_crypto_base64_encode(NULL, 0, &n, (const unsigned char *)user_info, strlen(user_info)); //Encode data of user_info

    digest = calloc(1, 6 + n + 1); //Allocates a block of memory for an array of 1 element with 6 + n + 1 bytes long
    if (digest)
    {
        strcpy(digest, "Basic ");
        esp_crypto_base64_encode((unsigned char *)digest + 6, n, (size_t *)&out, (const unsigned char *)user_info, strlen(user_info));
    }
    free(user_info);
    return digest;
}

#endif