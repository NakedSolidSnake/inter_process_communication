#include <consumer.h>
#include <led_process.h>
#include "led_pc.h"

int main (int argc, char *argv[])
{
    led_pc_t pc = 
    {
        .dummy = 0
    };

    led_process_t led;
    consumer_t consumer;

    consumer_args_t args = 
    {
        .argv = argv,
        .base = &led.base
    };

    led_process_init (&led);
    consumer_init (&consumer);

    led_process_open (&led, &pc);
    consumer_open (&consumer, &args);

    consumer_run (&consumer);

    consumer_close (&consumer);
    led_process_close (&led);

    return 0;
}