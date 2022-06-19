#ifndef BUTTON_PROCESS_H_
#define BUTTON_PROCESS_H_

#include <button_base.h>

typedef struct 
{
    button_base_t base;
    void *data;
} button_process_t;

bool button_process_init (button_process_t *button);
bool button_process_open (button_process_t *button, void *args);
bool button_process_close (button_process_t *button);

#endif /* BUTTON_PROCESS_H_ */
