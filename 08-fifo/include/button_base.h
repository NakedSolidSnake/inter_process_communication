#ifndef BUTTON_BASE_H_
#define BUTTON_BASE_H_

#include <stdbool.h>

typedef struct 
{
    void *object;
    bool (*init) (void *object);    
    bool (*read) (void *object);
} button_base_t;

#endif /* BUTTON_BASE_H_ */
