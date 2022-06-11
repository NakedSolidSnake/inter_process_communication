#include <led_process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <led.h>

static bool led_process_init_hardware (void *object)
{
    led_process_t *process = (led_process_t *)object;
    led_t *led = (led_t *)process->data;
    return led_init (led);
}   

static bool led_process_set (void *object, bool state)
{
    led_process_t *process = (led_process_t *)object;
    led_t *led = (led_t *)process->data;
    return led_set (led, state);
}

bool led_process_init (led_process_t *led)
{
    bool status = false;
    if (led != NULL)
    {
        memset (led, 0, sizeof (led_process_t));
        led->base.object = led;
        led->base.init = led_process_init_hardware;
        led->base.set = led_process_set;
        status = true;
    }

    return status;
}

bool led_process_open (led_process_t *led, void *args)
{
    bool status = false;
    if (led != NULL)
    {
        led->data = args;
        status = true;        
    }

    return status;
}

bool led_process_close (led_process_t *led)
{
    bool status = false;
    if (led != NULL)
    {
        memset (led, 0, sizeof (led_process_t));
        status = true;
    }

    return status;
}
