//
// Created by Jean-adrien on 19/06/17.
//

#include <string.h>
#include "stdio.h"
#include <zconf.h>
#include <printf.h>
#include "mendatory/my_stack.h"

static t_stack *rs = NULL;

char    *srv_read(void)
{
    char *s;

    if (rs == NULL)
        return (NULL);
    if (!(s = strdup(rs->data)))
        return (perror("strdup()"), NULL);
    rs = stack_delete(rs);
    return (s);
}

int server_download_data(int fd)
{
    char data[512];
    char *s;

    memset(data, 0, 512);
    if (read(fd, &data, 512) <= 0)
        return (1);
    s = strtok(data, "\n");
    while (s)
    {
        rs = stack_new(rs, s);
        s = strtok(NULL, "\n");
    }
    return (0);
}