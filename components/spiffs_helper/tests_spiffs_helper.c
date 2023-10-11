#include "tests_spiffs_helper.h"
#include "spiffs_helper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void tests_spiffs_helper_loop(){
    spiffs_helper_init();

    while(1)
    {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
}