#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include"driver/gpio.h"
#include"leds.h"
#include"connect.h"
#include "test_connect.h"
#include "nvs_flash.h"




void app_main(void)
{

    //led_initialize_blink(2, 500);

  nvs_flash_init();
  test_connect_main();

    while(1){
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}


