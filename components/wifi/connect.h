#ifndef __WIFI_CONNECT__
#define __WIFI_CONNECT__

void wifi_connect_initialize();
esp_err_t  wifi_connect_sta_start(char *ssid, char *pass) ;
void wifi_connect_ap_start(char *ssid, char *pass);
void wifi_connect_sta_stop();
void wifi_connect_ap_stop();

#endif