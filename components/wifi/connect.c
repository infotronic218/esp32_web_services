#include "connect.h"
#include "esp_wifi.h"


static void wifi_event_handler (void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

/**
 * @brief Initialize the wifi base function 
 * 
 */
void wifi_connect_initialize(){
    ESP_ERROR_CHECK(esp_netif_init()) ; // Initialize the network interface
    ESP_ERROR_CHECK(esp_event_loop_create_default()) ;
    wifi_init_config_t conf = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&conf));
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,    wifi_event_handler, NULL);
     esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP , wifi_event_handler, NULL);
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM));

}

/**
 * @brief Start the WIFI in station mode 
 * 
 * @param ssid The wifi name
 * @param pass The password 
 */
esp_err_t wifi_connect_sta_start(char *ssid, char *pass){

}
void wifi_connect_ap_start(char *ssid, char *pass){

}
void wifi_connect_sta_stop(){

}
void wifi_connect_ap_stop(){

}




static void wifi_event_handler (void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    
}