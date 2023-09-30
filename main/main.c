#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include"driver/gpio.h"

#define LED 2
void led_task(void *params);



void app_main(void)
{
    xTaskCreate(led_task, "LED Blinking", 1024, NULL, 5, NULL);

    while(1){
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}




void led_task(void *params ){
    // Pin configure 
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    static uint8_t state = 0;

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED, state);
        state =! state ;

    }

}