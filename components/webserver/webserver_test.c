#include "webserver_test.h"
#include "connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "file_manager_spiffs.h"
#include "stdio.h"
#include "cJSON.h"
#include "esp_wifi.h"


static  char *ssid = "Bbox-727DF9A6" ;
static  char *password= "c7HwHdEL33bhCJ4fVm";
static  char *TAG = "webserver";
static esp_err_t test_page_handler(httpd_req_t *req);
static esp_err_t on_default_handler(httpd_req_t *req);
static esp_err_t on_led_json_handler(httpd_req_t *req);
static esp_err_t on_api_wifi_scan_handler(httpd_req_t *req);

static char * BASE_PATH =  "/spiffs";

void webserver_test_loop(){
   wifi_connect_initialize() ;
   vTaskDelay(pdMS_TO_TICKS(1000));
   esp_err_t ret = wifi_connect_sta_start(ssid, password, 10000);
   webserver_mdns_start_service("sous", "Testing DNS");
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

   // JSON REQUEST 
   struct page_info_t led_control_info = {
     .method = HTTP_GET,
     .url = "/api/leds_json",
     .page_handler = on_led_json_handler 
   };
   webserver_register_page(server,&led_control_info);
   

  // JSON REQUEST 
   led_control_info.method = HTTP_POST;
   led_control_info.url = "/api/leds_json2";
   led_control_info.page_handler = on_led_json_handler;
   webserver_register_page(server,&led_control_info);

   // JSON REQUEST WIFI SCAN
   led_control_info.method = HTTP_GET;
   led_control_info.url = "/api/wifi_scan";
   led_control_info.page_handler = on_api_wifi_scan_handler;
   webserver_register_page(server,&led_control_info);
  

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





static esp_err_t on_led_json_handler(httpd_req_t *req){

 cJSON * data = cJSON_CreateObject();
 cJSON_AddBoolToObject(data, "state", false);
 cJSON_AddStringToObject(data, "name", "led1");
 
 char *json_text = cJSON_Print(data);
 ESP_LOGI(TAG, "JSON: %s", json_text);
 cJSON_Delete(data);
 httpd_resp_set_type(req, "text/json");
 httpd_resp_sendstr(req, json_text);
 return ESP_OK ;
}


static char *get_security_name(wifi_auth_mode_t mode);
wifi_ap_record_t records[20];
int count = 20 ;

static esp_err_t on_api_wifi_scan_handler(httpd_req_t *req){
  wifi_scan_config_t scan_config =  {
    .ssid =0 ,
    .bssid =0, 
    .channel =0,
    .show_hidden = true
  };

  esp_wifi_scan_start(&scan_config,  true);

 
  esp_wifi_scan_get_ap_records(&count,records);
  cJSON *data = cJSON_CreateArray();

  for(int i=0; i<count ;i++)
  {
    cJSON *row = cJSON_CreateObject();
    cJSON_AddStringToObject(row, "SSID", (char *)records[i].ssid);
    cJSON_AddNumberToObject(row, "CH", records[i].primary);
    cJSON_AddNumberToObject(row, "RSSI", records[i].rssi);
    cJSON_AddStringToObject(row, "authmode", (char *)get_security_name(records[i].authmode));
    cJSON_AddItemToArray(data, row);
    //cJSON_Delete(row);
  }

  char *data_json = cJSON_Print(data);

  cJSON_Delete(data);
  ESP_LOGI(TAG, "%s", data_json);
  httpd_resp_set_type(req, "text/json");
  httpd_resp_sendstr(req, data_json);
  return ESP_OK;

}

static char *get_security_name(wifi_auth_mode_t mode){
  switch (mode)
  {
  case   WIFI_AUTH_OPEN: return "OPEN" ; 
  case   WIFI_AUTH_WEP: return "WEP" ;             
  case   WIFI_AUTH_WPA_PSK: return "WPA_PSK" ;     
  case   WIFI_AUTH_WPA2_PSK: return "WPA2_PSK" ;      
  case   WIFI_AUTH_WPA_WPA2_PSK: return "WPA_WPA2_PSK" ;    
  case   WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2_ENTERPRISE" ;
  case   WIFI_AUTH_WPA3_PSK: return "WPA3_PSK" ;
  case   WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2_WPA3_PSK" ;
  case   WIFI_AUTH_WAPI_PSK: return "WAPI_PSK" ;
  case   WIFI_AUTH_OWE: return "OWE" ;
  case   WIFI_AUTH_MAX: return "MAX" ;
  default:
    return "NONE";
    break;
  }
}

 