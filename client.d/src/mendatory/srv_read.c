//
// Created by Jean-adrien on 19/06/17.
//

#include <stddef.h>
#include <string.h>
#include "mendatory/my_stack.h"

static t_stack *rs = NULL;

char    *srv_read(void)
{
    char *s;

    if (rs == NULL)
        return (NULL);
    if (!(s = strdup(rs->data)))
        return (NULL);
    stack_delete(rs);
    return (s);
}