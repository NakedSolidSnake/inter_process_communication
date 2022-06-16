#ifndef SHARED_FILE_H_
#define SHARED_FILE_H_

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct 
{
    const char *filename;
    int descriptor;
    int timeout;
    struct flock lock;
} shared_file_t;

bool shared_file_init (shared_file_t *sf);
bool shared_file_write (shared_file_t *sf, const char *data, uint32_t size);
bool shared_file_read (shared_file_t *sf, char *data, uint32_t *size);

#endif /* SHARED_FILE_H_ */
