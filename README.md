# Webserver section



# Custom partition table

* Copy the partitions file from ESP IDF folder (esp-idf/components/partitions/partitions_singleapp.csv)
* Adding new __row__ of type data
* Open menuconfig to set the partition to use the newly created __custom__ created.
* On the serial flasher increase the memory size to __4MB__ .

# Adding SPIFF folder to the cmake

'''
spiffs_create_partition_image(storage, ../spiffs_directory FLASH_IN_PROJECT)
'''


# mDNS Configuration

Congiguring the mDNS service to have a custom domain name in local for the ESP32

The __mDNS__ is no longer part of ESP-IDF in version 5. It should be added as 
an external library using __idf.py__ command line. 