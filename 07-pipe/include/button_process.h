#ifndef BUTTON_PROCESS_H_
#define BUTTON_PROCESS_H_

#include "button_base.h"

typedef struct 
{
    button_base_t *base;
    int descriptor;
} button_process_t;

typedef struct 
{
    button_base_t *base;
    char **argv;
} button_process_args_t;

bool button_process_init (button_process_t *button);
bool button_process_open (button_process_t *button, button_process_args_t *args);
bool button_process_run (button_process_t *button);
bool button_process_close (button_process_t *button);

#endif /* BUTTON_PROCESS_H_ */
