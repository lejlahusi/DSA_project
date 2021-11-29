#ifndef __POSTMETHOD_H
#define __POSTMETHOD_H
#include "string.h"
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <esp_http_server.h>
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "driver/gpio.h"
#include<stdlib.h>
#include<stdio.h>




#include "esp_http_client.h"

esp_err_t devices_post_handler(httpd_req_t *req);
esp_err_t devices_client_get_handler(httpd_req_t *req);


#endif

