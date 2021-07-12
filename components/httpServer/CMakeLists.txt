idf_component_register(SRCS "httpServer.c"
                    INCLUDE_DIRS "./include"
                    PRIV_REQUIRES nvs_flash esp_netif esp_eth protocol_examples_common)
