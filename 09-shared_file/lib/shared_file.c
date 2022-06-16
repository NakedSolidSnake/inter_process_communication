#include "shared_file.h"

static bool shared_file_create (shared_file_t *sf);
static bool shared_file_try_write_open (shared_file_t *sf);
static void shared_file_set_write_lock (shared_file_t *sf);
static void shared_file_try_lock (shared_file_t *sf);
static bool shared_file_try_unlock (shared_file_t *sf);

static bool shared_file_try_read_open (shared_file_t *sf);
static bool shared_file_is_unlock (shared_file_t *sf);
static void shared_file_set_read_lock (shared_file_t *sf);

bool shared_file_init (shared_file_t *sf)
{
    bool status = false;

    if (sf != NULL)
    {        
        status = shared_file_create (sf);
    }

    return status;
}

bool shared_file_write (shared_file_t *sf, const char *data, uint32_t size)
{
    bool status = false;

    if (sf != NULL && data != NULL && size > 0)
    {
        if (shared_file_try_write_open (sf) == true)
        {
            shared_file_set_write_lock (sf);
            shared_file_try_lock (sf);
            
            write (sf->descriptor, data, size);

            status = shared_file_try_unlock (sf);
        }        
    }

    return status;
}

bool shared_file_read (shared_file_t *sf, char *data, uint32_t *size)
{
    bool status = false;

    if (sf != NULL && data != NULL && *size > 0)
    {
        if (shared_file_try_read_open (sf) == true)
        {
            shared_file_set_write_lock (sf);

            if (shared_file_is_unlock (sf) == true)
            {
                shared_file_set_read_lock (sf);
                shared_file_try_lock (sf);

                while (read (sf->descriptor, data, *size) > 0);

                status = shared_file_try_unlock (sf);
            }        
        }
    }

    return status;
}

static bool shared_file_create (shared_file_t *sf)
{
    bool status = false;

    sf->descriptor = open (sf->filename, O_RDWR | O_CREAT, 0666);
    if (sf->descriptor >= 0)
    {
        write (sf->descriptor, "0", 1);
        close (sf->descriptor);
        status = true;
    }

    return status;    
}

static bool shared_file_try_write_open (shared_file_t *sf)
{
    sf->descriptor = open (sf->filename, O_RDWR, 0666);
    return sf->descriptor >= 0 ? true : false;
}

static void shared_file_set_write_lock (shared_file_t *sf)
{
    sf->lock.l_type = F_WRLCK;
    sf->lock.l_whence = SEEK_SET;
    sf->lock.l_start = 0;
    sf->lock.l_len = 0;
    sf->lock.l_pid = getpid ();
}

static void shared_file_try_lock (shared_file_t *sf)
{
    while (fcntl (sf->descriptor, F_SETLK, &sf->lock))
        usleep (sf->timeout);
}

static bool shared_file_try_unlock (shared_file_t *sf)
{
    bool status = false;

    sf->lock.l_type = F_UNLCK;

    if (fcntl (sf->descriptor, F_SETLK, &sf->lock) >= 0)
    {
        close (sf->descriptor);
        status = true;
    }

    return status;
}

static bool shared_file_try_read_open (shared_file_t *sf)
{
    sf->descriptor = open (sf->filename, O_RDONLY);
    return sf->descriptor >= 0 ? true : false;
}

static bool shared_file_is_unlock (shared_file_t *sf)
{
    bool status = false;

    while (fcntl (sf->descriptor, F_GETLK, &sf->lock) < 0)
        usleep (sf->timeout);

    if (sf->lock.l_type == F_UNLCK)
        status = true;

    else 
        close (sf->descriptor);

    return status;
}

static void shared_file_set_read_lock (shared_file_t *sf)
{
    sf->lock.l_type = F_RDLCK;
}