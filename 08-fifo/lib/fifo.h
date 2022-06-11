#ifndef FIFO_H_
#define FIFO_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct 
{
    const char *name;
    int descriptor;
} fifo_t;

bool fifo_init (fifo_t *fifo);
bool fifo_write (fifo_t *fifo, const char *data, uint32_t size);
bool fifo_read (fifo_t *fifo, char *data, uint32_t *size);
bool fifo_destroy (fifo_t *fifo);

#endif /* FIFO_H_ */
