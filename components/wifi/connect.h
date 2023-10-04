#ifndef __WIFI_CONNECT__
#define __WIFI_CONNECT__
#include "esp_err.h"

void wifi_connect_initialize();
esp_err_t  wifi_connect_sta_start(char *ssid, char *pass, int timeout_ms) ;
esp_err_t  wifi_connect_ap_start(char *ssid, char *pass);
void wifi_connect_sta_stop();
void wifi_connect_ap_stop();

#endif