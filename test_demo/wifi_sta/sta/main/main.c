#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"

#define TEST_SSID     "CMCC-Gm5z"
#define TEST_PASSWORD "vv3wedns"

#define TAG "sta"

/*回调函数*/
void wifi_event_handle(void* event_handler_arg,esp_event_base_t event_base,int32_t event_id,void* event_data)
{
    if(event_base == WIFI_EVENT)
    {
        switch(event_id)
        {
            case WIFI_EVENT_STA_START:
                esp_wifi_connect();
                break;
            case WIFI_EVENT_STA_CONNECTED:
                ESP_LOGI(TAG,"esp32 connected to ap!");
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                esp_wifi_connect();
                ESP_LOGI(TAG,"esp32 connect the ap faild!, retry");
                break;
            default:
                break;

        }
    }
    else if(event_base == IP_EVENT)
    {
        switch(event_id)
        {
            case IP_EVENT_STA_GOT_IP:
                ESP_LOGI(TAG,"esp32 get ip address!");       
                break;

        }   
    }    

}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_register(WIFI_EVENT,ESP_EVENT_ANY_ID,wifi_event_handle,NULL);//注册wifi事件
    esp_event_handler_register(IP_EVENT,IP_EVENT_STA_GOT_IP,wifi_event_handle,NULL);//注册IP事件

    wifi_config_t wifi_config = {
        .sta.threshold.authmode = WIFI_AUTH_WPA2_PSK,
        .sta.pmf_cfg.capable = true,
        .sta.pmf_cfg.required = false,

    };
    memset(&wifi_config.sta.ssid,0,sizeof(wifi_config.sta.ssid));
    memcpy(wifi_config.sta.ssid,TEST_SSID,strlen(TEST_SSID));

    memset(&wifi_config.sta.password,0,sizeof(wifi_config.sta.password));
    memcpy(wifi_config.sta.password,TEST_PASSWORD,strlen(TEST_PASSWORD));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA,&wifi_config)) ;
    ESP_ERROR_CHECK(esp_wifi_start());
}
