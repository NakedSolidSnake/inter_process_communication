#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "button_base.h"

typedef struct 
{
    button_base_t *base;
    int descriptor;
} producer_t;

typedef struct 
{
    button_base_t *base;
    char **argv;
} producer_args_t;

bool producer_init (producer_t *producer);
bool producer_open (producer_t *producer, producer_args_t *args);
bool producer_run (producer_t *producer);
bool producer_close (producer_t *producer);

#endif /* PRODUCER_H_ */
