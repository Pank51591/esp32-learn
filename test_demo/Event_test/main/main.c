/*
 * @Author: Panke pank51591@foxmail.com
 * @Date: 2024-09-14 16:05:09
 * @LastEditors: Panke pank51591@foxmail.com
 * @LastEditTime: 2024-09-27 10:59:05
 * @FilePath: \sample_project\main\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_log.h"


#define Num0_BIT  BIT0
#define Num1_BIT  BIT1

static EventGroupHandle_t test_event;

void taskA(void *param)
{
    //定时设置不同的事件位
    while(1)
    {
        xEventGroupSetBits(test_event,Num0_BIT);
        vTaskDelay(pdMS_TO_TICKS(1000));
        xEventGroupSetBits(test_event,Num1_BIT);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
     
}

void taskB(void *param)
{
    //等待事件位
    EventBits_t ev;
    while(1)
    {
        //等待在先前创建的事件组内设置一个或多个比特。
        ev = xEventGroupWaitBits(test_event,Num0_BIT|Num1_BIT,pdTRUE,pdFALSE,pdMS_TO_TICKS(5000));
        if(ev & Num0_BIT)
        {
            ESP_LOGI("ev","get BIT0 event");
            
        }
        if(ev & Num1_BIT)
        {
            ESP_LOGI("ev","get BIT1 event");

        }
    }

}

void app_main(void)
{
    test_event = xEventGroupCreate();

    xTaskCreate(taskA,"taskA",2048,NULL,3,NULL);     //3:优先级
    xTaskCreate(taskB,"taskB",2048,NULL,3,NULL);    

}
