#include "webserver_test.h"
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "file_manager_spiffs.h"
#include "stdio.h"

static  char *ssid = "Bbox-727DF9A6" ;
static  char *password= "c7HwHdEL33bhCJ4fVm";
static  char *TAG = "webserver";
static esp_err_t test_page_handler(httpd_req_t *req);
static esp_err_t on_default_handler(httpd_req_t *req);


static char * BASE_PATH =  "/spiffs";

void webserver_test_loop(){
   wifi_connect_initialize() ;
   vTaskDelay(pdMS_TO_TICKS(1000));
   esp_err_t ret = wifi_connect_sta_start(ssid, password, 10000);
   //wifi_connect_ap_start("Sous", "12345678");
  
  file_manager_spiffs_init(BASE_PATH);

   if(ret== ESP_OK){
    ESP_LOGI(TAG, "Starting the webserver");
   httpd_handle_t *server = webserver_start(true);

   struct page_info_t infos ={
      .method = HTTP_GET,
      .url = "/testing",
      .page_handler =  test_page_handler 
   };
   
   webserver_register_page(server,&infos);

   // ON DEFAULT URL 
   struct page_info_t on_default_infos = {
     .method = HTTP_GET,
     .url = "/*",
     .page_handler = on_default_handler 
   };

   webserver_register_page(server,&on_default_infos);

   
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
  
  FILE *file = file_manager_spiffs_get_file(BASE_PATH, "/index.html", "r");
  if(file==NULL)
  {
    ESP_LOGE(TAG, "Error reading the file");
    httpd_resp_send_404(req);
    return ESP_OK ;
  }


  char buffer[256];
  int bytes_read = 0 ;

   //char line[256];
    while((bytes_read=fread(buffer, sizeof(char), sizeof(buffer),file))>0){
       printf(buffer);
       httpd_resp_send_chunk(req, buffer, bytes_read);
    }
    httpd_resp_send_chunk(req, NULL, 0);

    fclose(file);  
  return ESP_OK ;
}

/**
 * @brief On default request handler 
 * 
 * @param req http request 
 * @return esp_err_t 
 */
static esp_err_t on_default_handler(httpd_req_t *req)
{
  char full_path[600];
  sprintf(full_path, "%s%s", BASE_PATH, req->uri);
  ESP_LOGI(TAG, "Path: %s", full_path);
  // LOAD THE FILE 
  FILE * file = file_manager_spiffs_get_file(BASE_PATH, req->uri, "r");
  // GET FILE EXTENSION
  char *ext = strrchr(req->uri, '.');
  
  if(ext){
    ESP_LOGI(TAG, "Extension: %s", ext);
    if(strcmp(ext, ".css")==0) httpd_resp_set_type(req,"text/css");
    if(strcmp(ext, ".js")==0) httpd_resp_set_type(req,"text/javascript");
    if(strcmp(ext, ".png")==0) httpd_resp_set_type(req,"image/png");
    if(strcmp(ext, ".jpg")==0) httpd_resp_set_type(req,"image/jpg");
   }

  if(file==NULL){
    file = file_manager_spiffs_get_file(BASE_PATH, "/index.html","r");
  }

  if(file==NULL){
     httpd_resp_send_404(req);
  }

  char buffer[1024];
  int read_bytes ;

  while((read_bytes=(fread(buffer, sizeof(char), sizeof(buffer), file)))>0){
    httpd_resp_send_chunk(req, buffer, read_bytes);
  }

  httpd_resp_send_chunk(req, NULL, 0);


  fclose(file);

 
  return ESP_OK ;
}