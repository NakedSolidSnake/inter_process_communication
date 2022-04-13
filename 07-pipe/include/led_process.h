#ifndef LED_PROCESS_H_
#define LED_PROCESS_H_

#include "led_base.h"

typedef struct 
{
    led_base_t *base;
    int descriptor;
} led_process_t;

typedef struct 
{
    led_base_t *base;
    char **argv;
} led_process_args_t;

bool led_process_init (led_process_t *led);
bool led_process_open (led_process_t *led, led_process_args_t *args);
bool led_process_run (led_process_t *led);
bool led_process_close (led_process_t *led);

#endif /* LED_PROCESS_H_ */
