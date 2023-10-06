#include "webserver_test.h"
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *ssid = "Bbox-727DF9A6" ;
static const char *password= "c7HwHdEL33bhCJ4fVm";
static const char *TAG = "webserver";


void webserver_test_loop(){
   //wifi_connect_initialize() ;
   vTaskDelay(pdMS_TO_TICKS(1000));
   esp_err_t ret = wifi_connect_sta_start(ssid, password, 10000);
   //wifi_connect_ap_start("Sous", "12345678");

   if(ret= ESP_OK){
    ESP_LOGI()
   }
    while(1)
    {
      vTaskDelay(1000);
    }
    

}
