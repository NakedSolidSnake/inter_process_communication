#include <consumer.h>
#include <led_process.h>
#include <led.h>

int main (int argc, char *argv[])
{
    led_t led = 
    {
        .gpio.pin = 0,
        .gpio.mode = gpio_mode_output
    };

    led_process_t process;
    consumer_t consumer;

    consumer_args_t args = 
    {
        .argv = argv,
        .base = &process.base
    };

    led_process_init (&process);
    consumer_init (&consumer);

    led_process_open (&process, &led);
    consumer_open (&consumer, &args);

    consumer_run (&consumer);

    consumer_close (&consumer);
    led_process_close (&process);

    return 0;
}