#include "webserver_test.h"
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_log.h"

static  char *ssid = "Bbox-727DF9A6" ;
static  char *password= "c7HwHdEL33bhCJ4fVm";
static  char *TAG = "webserver";
static esp_err_t test_page_handler(httpd_req_t *r);

void webserver_test_loop(){
   wifi_connect_initialize() ;
   vTaskDelay(pdMS_TO_TICKS(1000));
   esp_err_t ret = wifi_connect_sta_start(ssid, password, 10000);
   //wifi_connect_ap_start("Sous", "12345678");

   if(ret== ESP_OK){
    ESP_LOGI(TAG, "Starting the webserver");
   httpd_handle_t *server = webserver_start();
   struct page_info_t infos ={
      .method = HTTP_GET,
      .url = "/testing/*",
      .page_handler =  test_page_handler 
   };
   webserver_register_page(server,&infos);
   }else {
    ESP_LOGE(TAG, "Not able to start the server");
   }
    while(1)
    {
      vTaskDelay(1000);
    }
    

}


static esp_err_t test_page_handler(httpd_req_t *r){

  httpd_resp_sendstr(r, "<h1>Hello my friend ! How are you .</h1>");
  return ESP_OK ;
}