/*
** my_stack.h for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/include/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 21:09:48 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:09:48 2017 vincent.mesquita@epitech.eu
*/

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
