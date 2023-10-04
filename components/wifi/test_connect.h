#ifndef __CONNECT_TEST__
#define __CONNECT_TEST__
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

static const char *ssid = "Bbox-727DF9A6" ;
static const char *password= "c7HwHdEL33bhCJ4fVm";
static const char *TAG = "wifi_connect";


void test_connect_main()
{

   wifi_connect_initialize() ;
   vTaskDelay(pdMS_TO_TICKS(1000));
   //wifi_connect_sta_start(ssid, password, 10000);
   wifi_connect_ap_start("Sous", "12345678");
    while(1)
    {
      vTaskDelay(1000);
    }
}


#endif