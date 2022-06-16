#ifndef LED_PROCESS_H_
#define LED_PROCESS_H_

#include <led_base.h>

typedef struct 
{
    led_base_t base;
    void *data;
} led_process_t;

bool led_process_init (led_process_t *led);
bool led_process_open (led_process_t *led, void *args);
bool led_process_close (led_process_t *led);

#endif /* LED_PROCESS_H_ */
