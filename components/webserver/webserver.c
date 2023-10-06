#include "webserver.h"
#include "esp_http_server.h"

 static esp_err_t on_default_url(httpd_req_t *r);

void webserver_start()
{
    httpd_handle_t server = NULL ;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_ERROR_CHECK(httpd_start(&server, &config));

    httpd_uri_t default_url = {
        .method = HTTP_GET,
        .handler = on_default_url,
        .uri = "/"
    };

    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &default_url));

}

void webserver_stop()
{

}


 esp_err_t on_default_url(httpd_req_t *r){
    return ESP_OK;
 }