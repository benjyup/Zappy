//
// Created by Jean-Adrien on 19/06/17.
//

#ifndef MY_STACK_H_
# define MY_STACK_H_

typedef struct      e_stack
{
    char            *data;
    char            *ptr;
    struct e_stack  *next;
}               t_stack;

t_stack *stack_new(t_stack *stack, const char *string);
t_stack *stack_delete(t_stack *stack);
t_stack    *stack_flush(t_stack *stack);

#endif /* !MY_STACK_H_ */
