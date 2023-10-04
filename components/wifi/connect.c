#include "connect.h"
#include "esp_wifi.h"
#include <string.h>
#include "esp_log.h"
#include "freertos/event_groups.h"
static char * TAG = "wifi_connect" ;


static EventGroupHandle_t connect_events;
enum Connect_Events {
   CONNECT_STA_GOT_IP= BIT0,
   CONNECT_STA_DISCONNECTED = BIT1
};

char *get_wifi_disconnection_string(wifi_err_reason_t wifi_err_reason);
static void wifi_event_handler (void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
static void ip_event_handler (void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

/**
 * @brief Initialize the wifi base function  
 */
void wifi_connect_initialize(){
    ESP_ERROR_CHECK(esp_netif_init()) ; // Initialize the network interface
    ESP_ERROR_CHECK(esp_event_loop_create_default()) ;
    wifi_init_config_t conf = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&conf));
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,    wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID , ip_event_handler, NULL);
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM));
}

/**
 * @brief Start the WIFI in station mode 
 * @param ssid The wifi name
 * @param pass The password 
 * @param timeout_ms Timeout 
 */
esp_err_t wifi_connect_sta_start(char *ssid, char *pass, int timeout_ms)
{
    esp_err_t ret ;
    connect_events = xEventGroupCreate();
    esp_netif_t * network_interface = esp_netif_create_default_wifi_sta();

    wifi_config_t wifi_conf;
    memset(&wifi_conf, 0, sizeof(wifi_conf));
    strncpy((char*)wifi_conf.sta.ssid, ssid, sizeof(wifi_conf.sta.ssid)-1);
    strncpy((char*)wifi_conf.sta.password, pass, sizeof(wifi_conf.sta.password)-1);

    ret = esp_wifi_set_mode(WIFI_MODE_STA);
    ret = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_conf);
    esp_wifi_start();
    EventBits_t result = xEventGroupWaitBits(connect_events, CONNECT_STA_GOT_IP| CONNECT_STA_DISCONNECTED, pdTRUE,pdFALSE, pdMS_TO_TICKS(timeout_ms)) ;
    
    if(result==CONNECT_STA_GOT_IP){
        return ESP_OK;
    }
    return ESP_FAIL;
}

esp_err_t wifi_connect_ap_start(char *ssid, char *pass){
     esp_netif_t * network_interface = esp_netif_create_default_wifi_ap();
     wifi_config_t wifi_conf ;
     memset(&wifi_conf, 0, sizeof(wifi_conf));

     strncpy((char*)wifi_conf.ap.ssid, ssid, sizeof(wifi_conf.ap.ssid)-1);
     strncpy((char*)wifi_conf.ap.password, pass, sizeof(wifi_conf.ap.password)-1 );
     wifi_conf.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
     wifi_conf.ap.max_connection = 5;
     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_conf));
     ESP_ERROR_CHECK(esp_wifi_start());

     return ESP_OK ;

}


/**
 * @brief Stop the wifi in station mmode 
 */
void wifi_connect_sta_stop(){
      ESP_ERROR_CHECK(esp_wifi_disconnect());
      ESP_ERROR_CHECK(esp_wifi_stop());
}

/**
 * @brief Stop the Access point of the wifi and 
 */
void wifi_connect_ap_stop(){
      ESP_ERROR_CHECK(esp_wifi_disconnect());
      ESP_ERROR_CHECK(esp_wifi_stop());
}





static void wifi_event_handler (void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START: 
        {
            ESP_LOGI(TAG, "Connecting ...");
            ESP_ERROR_CHECK(esp_wifi_connect()) ;
        }break;
    case WIFI_EVENT_STA_STOP :
    {
        ESP_LOGI(TAG, "Wifi STA Stoped");
    }break;

    case WIFI_EVENT_STA_CONNECTED:
    {
        ESP_LOGI(TAG, "Station connected");
        
        
    }break;
    
    case WIFI_EVENT_STA_DISCONNECTED:
    {
        ESP_LOGI(TAG, "STA Disconnected");
        xEventGroupSetBits(connect_events, CONNECT_STA_DISCONNECTED);
        wifi_event_sta_disconnected_t *sta_event = (event_data);
        if(sta_event->reason == WIFI_REASON_ASSOC_LEAVE){
            ESP_LOGI(TAG, "Disconnected on purpose");
        }else{
          char *reason  = get_wifi_disconnection_string(sta_event->reason);
          ESP_LOGE(TAG, "Reason : %s ", reason);
        }
    }break;

    default:
        break;
    }
}


static void ip_event_handler (void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{

    switch (event_id)
    {
    case IP_EVENT_STA_GOT_IP:
    {
        ESP_LOGI(TAG, "STA Got IP");
        xEventGroupSetBits(connect_events, CONNECT_STA_GOT_IP);
    }
        break;
    default:
        break;
    }
}


