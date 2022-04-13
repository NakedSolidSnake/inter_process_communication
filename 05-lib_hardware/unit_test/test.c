#include <button.h>
#include <led.h>
#include <unistd.h>
#include <stdlib.h>

#define TEST_1MS    1000

static void input_handler (void);
static bool state = false;

static led_t led = 
{
    .gpio.pin = 0,
    .gpio.mode = gpio_mode_output
};

static button_t button = 
{
    .gpio.pin = 7,
    .gpio.mode = gpio_mode_input,
    .pull_mode = button_mode_pullup,
    .edge = button_edge_falling,
    .event = input_handler
};

int main (int argc, char *argv[])
{   
    led_state_t led_state = led_state_low;

    if (button_init (&button) == false)
        return EXIT_FAILURE;

    if (led_init (&led) == false)
        return EXIT_FAILURE;

    while (true)
    {
        if (state == true)
        {
            led_set (&led, led_state);
            if (led_state == led_state_low)
                led_state = led_state_high;
            else 
                led_state = led_state_low;

            state = false;
        }

        usleep (TEST_1MS);
    }

    return 0;
}

static void input_handler (void)
{
    if (button_read (&button) == true)
    {
        usleep (TEST_1MS * 200);
        while (button_read (&button) == true);
        state = true;
    }
}