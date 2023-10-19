#ifndef LEDS_ 
#define LEDS_ 
#include<inttypes.h>


void led_initialize_blink(uint8_t pin_, int delay_us);
void led_initialize_simple(uint8_t pin_);
void led_set_state(uint8_t pin_, uint8_t state) ;
#endif