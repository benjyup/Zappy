//
// Created by Jean-Adrien on 19/06/17.
//


#include <stddef.h>
#include "mendatory/my_stack.h"

static t_stack *ws = NULL;

int srv_write(const char *s)
{
    if (stack_new(ws, s))
        return (-1);
    return (0);
}