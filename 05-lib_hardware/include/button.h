#ifndef BUTTON_H_
#define BUTTON_H_

#include <gpio.h>

typedef void (*button_event_t) (void);

typedef enum 
{
    button_mode_pulloff = 0,
    button_mode_pulldown,
    button_mode_pullup
} button_pull_mode_t;

typedef enum 
{
    button_edge_setup = 0,
    button_edge_falling,
    button_edge_rising,
    button_edge_both
} button_int_edge_t;

typedef struct 
{
    gpio_t gpio;
    button_pull_mode_t pull_mode;
    button_int_edge_t edge;
    button_event_t event;
} button_t;

bool button_init (button_t *button);

bool button_read (button_t *button);

#endif /* BUTTON_H_ */
