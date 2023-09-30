#include "leds.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


static char * task_name = "blink" ;
static int task_stack =  1024 * 5 ;
static int delay = 1000 ;
static uint8_t pin;


struct LedInfo
{
   uint8_t pin ;
   int delay_us; 
};

static struct LedInfo led;

static void blink(void *params) ;

void led_initialize_blink(uint8_t pin_, int delay_){
    led.delay_us = delay_ ;
    led.pin = pin_;
    xTaskCreate(blink, task_name, task_stack , NULL, 5, NULL );
}

static void blink(void *params){
    gpio_set_direction(led.pin, GPIO_MODE_OUTPUT);
    uint8_t state = 0 ;
   while(1)
   {
    printf("Running the blink function\n\r");
     vTaskDelay(pdMS_TO_TICKS(led.delay_us));
     gpio_set_level(led.pin, state );
     state= !state ;

   }
}

