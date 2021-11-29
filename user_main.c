#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "debug.h"
#include "wifi.h"
#include "sensors.h"
#include "postmethod.h"
//#include "elements.h"
#define EXAMPLE_ESP_WIFI_SSID      "b5092a"
#define EXAMPLE_ESP_WIFI_PASS      "330273020"
esp_err_t _http_event_handle(esp_http_client_event_t *evt);
static const char* TAG = "MyModule";
/*extern struct device{
int id;
int value;
char device_details[50];

};
char sendBuffer [200]={""};
extern  ser;
extern LED;
extern  LLED;
extern  mmotion;
extern struct device LLDR;
extern struct device ultrason;
extern struct device devices[10];*/
void app_main()
{
    initDEBUG("", '5', 921600, "DSA - Debug example");
    ESP_ERROR_CHECK(nvs_flash_init());

    initWIFI("b5092a","330273020");
    adc();
    
    LDR_init();
 
    hcsr_init();
 
    motion_init();
 printDEBUG(DSYS,"MOTION\n");

        ser.id=1;
        strcpy(ser.device_details,"output-door-Garage_Door#");
        ser.value=servo();



        LED.id = 2;
        strcpy(LED.device_details,"output-light-Garden_Light#");
        LED.value = 0;


        LLED.id = 3;
        strcpy(LLED.device_details,"output-light-Kitchen_Light#");
        LLED.value = 1;
int motion=motion_detection();
printDEBUG(DSYS,"motion %d\n",motion);

        mmotion.id=4;
        strcpy(mmotion.device_details,"nesto3#");
        mmotion.value=motion;
int ldr=LDR_output();
printDEBUG(DSYS,"ldr %d\n",ldr);

        LLDR.id=5;
        strcpy(LLDR.device_details,"nesto2#");
        LLDR.value=ldr;

int distance=get_ultrasonic();
printDEBUG(DSYS,"distance %d\n",distance);

        ultrason.id=6;
        strcpy(ultrason.device_details,"nesto1#");
        ultrason.value=distance;


int numberOfDevices=6;
devices[0]=ser;
devices[1]=LED;
devices[2]=LLED;
devices[3]=mmotion;
devices[4]=LLDR;
devices[5]=ultrason;


    const char template[100] = {"%d-%d-%s"};

    for( int i = 0; i < numberOfDevices;i++){
        if(i == 0){

            // 0 indicating boardID
            strcat(sendBuffer,"0#");
        }
        char temp[50];
        snprintf(temp,sizeof temp,template,devices[i].id,devices[i].value,devices[i].device_details);
        strcat(sendBuffer,temp);
    }
    // printf("Works");

    printDEBUG(DSYS,"%s",sendBuffer);
   
/*	while(1){
	int bright=LDR_output();
	printDEBUG(DSYS,"BRIGHTNESS %d\n",bright);
	vTaskDelay(1000/portTICK_RATE_MS);
	uint8_t distance=get_ultrasonic();
	printDEBUG(DSYS,"distance %d\n",distance);
	}
*/
esp_http_client_config_t config = {
   .url = "192.168.0.1/devices",
   .event_handler = _http_event_handle,
};
esp_http_client_handle_t client = esp_http_client_init(&config);
esp_err_t err = esp_http_client_perform(client);

if (err == ESP_OK) {
   ESP_LOGI(TAG, "Status = %d, content_length = %d",
           esp_http_client_get_status_code(client),
           esp_http_client_get_content_length(client));
}
esp_http_client_cleanup(client);

esp_http_client_set_post_field(client,&sendBuffer,200);



}


esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
            printf("%.*s", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

