#ifndef __WEBSERVER__
#define __WEBSERVER__
#include "esp_log.h"
#include "esp_http_server.h"
httpd_handle_t  webserver_start(bool wild_card);

struct  page_info_t {
  const char * url;
  esp_err_t (*page_handler)(httpd_req_t *r);
  httpd_method_t  method ;
};

void webserver_register_page(httpd_handle_t server, struct page_info_t *infos );
void webserver_stop();


#endif