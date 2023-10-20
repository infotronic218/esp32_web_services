#include "webserver.h"
#include "mdns.h"


static httpd_handle_t server3 ;

static char * TAG = "webserver" ;
static char * BASE_PATH =  "/spiffs";


httpd_handle_t  webserver_start(bool wildcard)
{
    httpd_handle_t server = NULL ;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = config.stack_size * 2;
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

/**
 * @brief Start the mDNS service on the ESP32
 * 
 * @return esp_err_t 
 */
esp_err_t webserver_mdns_start_service(const char *hostname, const char * instance){
 ESP_ERROR_CHECK( mdns_init());
 ESP_ERROR_CHECK( mdns_hostname_set(hostname) );
 ESP_LOGI(TAG, "mdns name set to : %s", hostname);
 ESP_ERROR_CHECK( mdns_instance_name_set(instance) );

 return ESP_OK ;
}
void webserver_stop()
{

}


 