#include "spiffs_helper.h"
#include "esp_spiffs.h"

static char * TAG = "spiffs_helper";
void spiffs_helper_init()
{
    esp_vfs_spiffs_conf_t config = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5 ,
        .format_if_mount_failed = true 
    };

    esp_vfs_spiffs_register(&config);
    FILE *file =  fopen("/spiffs/index.html", "r");

    if(file==NULL){
        ESP_LOGE(TAG, "Error opening the file");
        return;
    }

    char line[256];
    while(fgets(line, sizeof(line), file)!=NULL){
       printf(line);
    }

    fclose(file);

    esp_vfs_spiffs_unregister(NULL);

}
