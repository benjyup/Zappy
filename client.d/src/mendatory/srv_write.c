//
// Created by Jean-Adrien on 19/06/17.
//

#include <zconf.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include "mendatory/my_stack.h"

static t_stack *ws = NULL;
static pthread_mutex_t mutex_write = PTHREAD_MUTEX_INITIALIZER;

int srv_write(const char *s)
{
    pthread_mutex_lock(&mutex_write);
    if (!(ws = stack_new(ws, s)))
    {
        pthread_mutex_unlock(&mutex_write);
        return (-1);
    }
    pthread_mutex_unlock(&mutex_write);
    return (0);
}

int server_upload_data(int fd)
{
    int ret;
    int size;

    pthread_mutex_lock(&mutex_write);
    if (ws != NULL && ws->data != NULL)
    {
        size = strlen(ws->ptr);
        if ((ret = write(fd, ws->ptr, size)) == -1)
        {
            pthread_mutex_unlock(&mutex_write);
            return (perror("write()"), 1);
        }
        if (ret != size)
        {
            ws->ptr += ret;
            pthread_mutex_unlock(&mutex_write);
            return (0);
        }
        ws = stack_delete(ws);
    }
    pthread_mutex_unlock(&mutex_write);
    return (0);
}