#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


void taskA(void* param)
{
    while(1)
    {
        ESP_LOGI("main","HEllo World!");
        vTaskDelay(pdMS_TO_TICKS(500));

    }

}


void app_main(void)
{
    xTaskCreate(taskA,"hello world",2048,NULL,3,NULL);
}
