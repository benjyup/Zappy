//
// Created by Jean-adrien on 19/06/17.
//

#include <string.h>
#include <pthread.h>
#include "stdio.h"
#include <zconf.h>
#include <printf.h>
#include "mendatory/my_stack.h"

static t_stack *rs = NULL;
static pthread_mutex_t mutex_read = PTHREAD_MUTEX_INITIALIZER;

char    *srv_read(void)
{
    char *s;

    pthread_mutex_lock(&mutex_read);
    if (rs == NULL)
    {
        pthread_mutex_unlock(&mutex_read);
        return (NULL);
    }
    if (!(s = strdup(rs->data)))
    {
        pthread_mutex_unlock(&mutex_read);
        return (NULL);
    }
    rs = stack_delete(rs);
    pthread_mutex_unlock(&mutex_read);
    return (s);
}

int server_download_data(int fd)
{
    char data[512];

    memset(data, 0, 512);
    pthread_mutex_lock(&mutex_read);
    if (read(fd, &data, 512) <= 0)
    {
        pthread_mutex_unlock(&mutex_read);
        return (1);
    }
    rs = stack_new(rs, data);
    pthread_mutex_unlock(&mutex_read);
    return (0);
}