#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include"driver/gpio.h"
#include"leds.h"





void app_main(void)
{

    led_initialize_blink(2, 500);
  

    while(1){
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}


