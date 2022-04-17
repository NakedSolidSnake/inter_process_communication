#include <producer.h>
#include <button_process.h>
#include <stdlib.h>
#include <button.h>

int main (int argc, char *argv[])
{
    button_t button = 
    {
        .gpio.pin = 7,
        .gpio.mode = gpio_mode_input,
        .pull_mode = button_mode_pullup,
        .edge = button_edge_falling,
        .event = NULL
    };

    button_process_t process;
    producer_t producer;

    producer_args_t args = 
    {
        .argv = argv,
        .base = &process.base
    };

    button_process_init (&process);
    producer_init (&producer);

    button_process_open (&process, &button);
    producer_open (&producer, &args);

    producer_run (&producer);

    producer_close (&producer);
    button_process_close (&process);

    return 0;
}