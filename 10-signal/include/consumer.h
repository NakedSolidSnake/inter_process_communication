#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "led_base.h"

typedef struct 
{
    led_base_t *base;    
} consumer_t;

typedef struct 
{    
    led_base_t *base;
    char **argv;
} consumer_args_t;

bool consumer_init (consumer_t *consumer);
bool consumer_open (consumer_t *consumer, consumer_args_t *args);
bool consumer_run (consumer_t *consumer);
bool consumer_close (consumer_t *consumer);

#endif /* CONSUMER_H_ */
