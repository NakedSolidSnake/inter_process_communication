#include <gpio.h>
#include <stdlib.h>
#include <wiringPi.h>

bool gpio_init (gpio_t *gpio)
{
    bool status = false;

    if (gpio != NULL)
    {
        wiringPiSetup ();
        pinMode (gpio->pin, gpio->mode);
        status = true;
    }

    return status;
}