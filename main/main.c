#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include"driver/gpio.h"

#define LED 4 
void led_task(void *params);



void app_main(void)
{
    xTaskCreate(led_task, "LED Blinking", 1024, NULL, 5, NULL);

}




void led_task(void *params ){
    // Pin configure 
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    static uint8_t state = 0;

    while(1)
    {
        vTaskDelay(1000);
        gpio_set_level(LED, state);

    }

}