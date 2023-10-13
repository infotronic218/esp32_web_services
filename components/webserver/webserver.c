#include "webserver.h"
#include "spiffs_helper.h"

static httpd_handle_t server3 ;

static char * TAG = "webserver" ;
static char * BASE_PATH =  "/spiffs";
static esp_err_t on_default_url(httpd_req_t *r);

httpd_handle_t  webserver_start(bool wildcard)
{
    httpd_handle_t server = NULL ;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    // Attach the wildcard handler
    if(wildcard) { config.uri_match_fn = httpd_uri_match_wildcard ;}

    ESP_ERROR_CHECK(httpd_start(&server, &config));

  if(server==NULL){
    return NULL ;
  }
  //httpd_handle_t* server2 = &server ;
  return server ;
}


void webserver_register_page(httpd_handle_t server, struct page_info_t *infos ){
    if(server==NULL){ 
        ESP_LOGE(TAG, "Page url %s , registration error", infos->url);
        return ;
    }
    httpd_uri_t page_uri ={
        .handler = infos->page_handler,
        .method = infos->method,
        .uri = infos->url
    };
   
   ESP_ERROR_CHECK( httpd_register_uri_handler(server, &page_uri));
   ESP_LOGI(TAG, "Page with [URL: %s ]  registered successfully ", infos->url);
}

void webserver_stop()
{

}


 esp_err_t on_default_url(httpd_req_t *r){
    ESP_LOGI(TAG, "New Request on the server");
    
    httpd_resp_sendstr(r, "<h1>Hello world </h1>");

    return ESP_OK;
 }