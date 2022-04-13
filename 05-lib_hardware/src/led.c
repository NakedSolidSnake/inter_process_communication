#include <led.h>
#include <stdlib.h>
#include <wiringPi.h>

bool led_init (led_t *led)
{
    bool status = false;

    if (led != NULL)
    {
        status = gpio_init ((gpio_t *)led);
    }

    return status;
}

bool led_set (led_t *led, led_state_t state)
{
    bool status = false;

    if (led != NULL)
    {
        digitalWrite (((gpio_t *)led)->pin, state);
        status = true;
    }

    return status;
}