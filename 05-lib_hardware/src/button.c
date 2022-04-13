#include <button.h>
#include <stdlib.h>
#include <wiringPi.h>

bool button_init (button_t *button)
{
    bool status = false;

    if (button != NULL)
    {

        status = gpio_init ((gpio_t *)button);
        pullUpDnControl (((gpio_t *)button)->pin, button->pull_mode);

        if (button->event)
            wiringPiISR (((gpio_t *)button)->pin, button->edge, button->event);
    }

    return status;
}

bool button_read (button_t *button)
{
    bool status = false;

    if (button != NULL)
    {
        status = (bool) digitalRead (((gpio_t *)button)->pin);
    }

    return status;
}