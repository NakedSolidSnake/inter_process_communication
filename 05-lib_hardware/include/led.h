#ifndef LED_H_
#define LED_H_

#include <gpio.h>

typedef enum 
{
    led_state_low = 0,
    led_state_high
} led_state_t;

typedef struct 
{
    gpio_t gpio;
} led_t;

bool led_init (led_t *led);
bool led_set (led_t *led, led_state_t state);

#endif /* LED_H_ */
