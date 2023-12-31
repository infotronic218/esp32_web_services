#ifndef __SPI_FILES__
#define __SPI_FILES__
#include <stdint.h>
#include <stdio.h>
#include "esp_err.h"

#include "esp_log.h"
esp_err_t file_manager_spiffs_init(char *base_path);
esp_err_t file_manager_spiffs_deinit();
/*esp_err_t spiffs_helper_get_file(char *base_path,char *path, char *mode,  FILE *found_file);*/
FILE *file_manager_spiffs_get_file(char *base_path, char *path, char *mode);
#endif