#include <producer.h>
#include <button_process.h>
#include "button_pc.h"

int main (int argc, char *argv[])
{
    button_pc_t pc = 
    {
        .fifo = "/tmp/button"
    };

    button_process_t button;
    producer_t producer;

    producer_args_t args = 
    {
        .argv = argv,
        .base = &button.base
    };

    button_process_init (&button);
    producer_init (&producer);

    button_process_open (&button, &pc);
    producer_open (&producer, &args);

    producer_run (&producer);

    producer_close (&producer);
    button_process_close (&button);

    return 0;
}