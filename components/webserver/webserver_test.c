#include "webserver_test.h"
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "spiffs_helper.h"
#include "stdio.h"

static  char *ssid = "Bbox-727DF9A6" ;
static  char *password= "c7HwHdEL33bhCJ4fVm";
static  char *TAG = "webserver";
static esp_err_t test_page_handler(httpd_req_t *r);

static char * BASE_PATH =  "/spiffs";

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
      .url = "/testing",
      .page_handler =  test_page_handler 
   };
   spiffs_helper_init(BASE_PATH);
   webserver_register_page(server,&infos);
   
   }else {
    ESP_LOGE(TAG, "Not able to start the server");
   }
    while(1)
    {
      vTaskDelay(1000);
    }
    

}


static esp_err_t test_page_handler(httpd_req_t *req){
  //httpd_resp_sendstr(r, "<h1>Hello my friend ! How are you .</h1>");
  
  FILE *file = NULL ;
  esp_err_t ret = spiffs_helper_get_file(BASE_PATH, "/index.html", "r", &file);
  if(ret!=ESP_OK)
  {
    ESP_LOGE(TAG, "Error reading the file");
    httpd_resp_send_404(req);
    return ESP_OK ;
  }

  if(file==NULL)
  {
    ESP_LOGE(TAG, "File is null");
    return ESP_OK;
  }

  char line[256];
  int bytes_read = 0 ;

   //char line[256];
    while(fgets(line, sizeof(line), file)!=NULL){
       printf(line);
    }

    fclose(file);
/*
  while((bytes_read = fread(line, sizeof(char),sizeof(line), file ))>0){
      httpd_resp_send_chunk(req, line, bytes_read);
  }
  httpd_resp_send_chunk(req, NULL, 0);*/
  


  
  return ESP_OK ;
}