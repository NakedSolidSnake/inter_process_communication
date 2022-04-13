#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>

typedef enum 
{
    gpio_mode_input = 0,
    gpio_mode_output
} gpio_mode_t;

typedef struct 
{
    int pin;
    gpio_mode_t mode;
} gpio_t;


bool gpio_init (gpio_t *gpio);

#endif /* GPIO_H_ */
