#include "tests_spiffs_helper.h"
#include "spiffs_helper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"
static char * BASE_PATH = "/spiffs";

void tests_spiffs_helper_loop(){
    
    esp_err_t ret = spiffs_helper_init(BASE_PATH);
    if(ret!=ESP_OK){
       printf("Error initializing the file");
    }
     
     FILE * file = spiffs_helper_get_file(BASE_PATH, "/index.html","r");
     
    while(1)
    {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
}