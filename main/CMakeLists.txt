idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ".")


#spiffs_create_partition_image(storage ../spiffs_directory FLASH_IN_PROJECT)
#spiffs_create_partition_image(storage ../spiffs_directory FLASH_IN_PROJECT)

spiffs_create_partition_image(storage ../web_pages/esp_vue/dist FLASH_IN_PROJECT)