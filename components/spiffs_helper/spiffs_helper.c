#include "spiffs_helper.h"
#include "esp_spiffs.h"
#include "string.h"

static char * TAG = "spiffs_helper";

/**
 * @brief Initialize SPIFFS with a base directory 
 * 
 * @param base_path The base path of SPIFFS
 * @return esp_err_t return ESP_OK when the initialization went correctly and ESP_FAIL when not
 */
esp_err_t spiffs_helper_init(char *base_path)
{
    esp_vfs_spiffs_conf_t config = {
        .base_path = base_path,
        .partition_label = NULL,
        .max_files = 5 ,
        .format_if_mount_failed = true 
    };

    esp_err_t ret =  esp_vfs_spiffs_register(&config);
    ESP_ERROR_CHECK(ret);
    if (ret!= ESP_OK){
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Initialized successfully");
    return ESP_OK ;
    /*FILE *file =  fopen("/spiffs/index.html", "r");

    if(file==NULL){
        ESP_LOGE(TAG, "Error opening the file");
        return;
    }

    char line[256];
    while(fgets(line, sizeof(line), file)!=NULL){
       printf(line);
    }

    fclose(file);

    esp_vfs_spiffs_unregister(NULL);*/

}

esp_err_t spiffs_helper_deinit(){
    return esp_vfs_spiffs_unregister(NULL);
}


/**
 * @brief Read file from SPIFFS directory
 * 
 * @param base_path The base path where SPIFFS is initialized
 * @param path  The file relative path 
 * @param mode  Open the file in read or write mode
 * @param found_file Pointer to the file when it exists
 * @return esp_err_t  ESP_OK when the file is found and ESP_FAILL when not 
 */
esp_err_t spiffs_helper_get_file(char *base_path,char *path, char *mode, FILE *found_file){
    char full_path[100];
    memset(full_path, 0, sizeof(full_path));
    sprintf(full_path, "%s%s", base_path, path);
    ESP_LOGI(TAG,"Full path : %s", full_path);
    found_file = fopen(full_path, mode);
    if(found_file!=NULL){
        
        ESP_LOGI(TAG, "%s File read SUCCESS", full_path);
        return ESP_OK ;
    }
    found_file = NULL ;
    ESP_LOGE(TAG, "%s File read ERROR", full_path);
    return ESP_FAIL ;
}