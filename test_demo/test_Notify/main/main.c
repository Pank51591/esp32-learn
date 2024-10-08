/*
 * @Author: Panke pank51591@foxmail.com
 * @Date: 2024-09-14 16:05:09
 * @LastEditors: Panke pank51591@foxmail.com
 * @LastEditTime: 2024-09-27 14:20:08
 * @FilePath: \sample_project\main\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "../build/config/sdkconfig.h"


static TaskHandle_t taskA_handle;
static TaskHandle_t taskB_handle;

void taskA(void *param)
{
    uint32_t value = 0;
    vTaskDelay(pdMS_TO_TICKS(20));
    while(1)
    {
        xTaskNotify(taskB_handle,value,eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(1000));
        value++;
    }
}

void taskB(void *param)
{
    //接收任务通知并打印
    uint32_t value;
    while(1)
    {
        xTaskNotifyWait(0x00,ULONG_MAX,&value,portMAX_DELAY);
        ESP_LOGI("ev","notify wait value: %lu ",value);

    }

}


void app_main(void)
{
    xTaskCreatePinnedToCore(taskA,"taskA",2048,NULL,3,&taskA_handle,1);
    xTaskCreatePinnedToCore(taskB,"taskB",2048,NULL,3,&taskB_handle,1);
}
