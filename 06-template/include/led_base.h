#ifndef LED_BASE_H_
#define LED_BASE_H_

#include <stdbool.h>

typedef struct 
{
    void *object;
    bool (*init) (void *object);
    bool (*set) (void *object, bool state);
} led_base_t;

#endif /* LED_BASE_H_ */
