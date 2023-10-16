#ifndef __WEBSERVER__
#define __WEBSERVER__
#include "esp_log.h"
#include "esp_err.h"
#include "esp_http_server.h"
httpd_handle_t  webserver_start(bool wild_card);

struct  page_info_t {
  const char * url;
  esp_err_t (*page_handler)(httpd_req_t *r);
  httpd_method_t  method ;
};

void webserver_register_page(httpd_handle_t server, struct page_info_t *infos );
esp_err_t webserver_mdns_start_service(const char *hostname, const char * instance);
void webserver_stop();


#endif