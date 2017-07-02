/*
** argument.c for  in /home/kyxo/rendu/Reseau/zappy/PSU_2016_zappy/client/src/mendatory
** 
** Made by Vincent
** Login   <florian.vincent@epitech.eu>
** 
** Started on  Sun Jul  2 22:35:26 2017 Vincent
** Last update Sun Jul  2 22:38:38 2017 Vincent
*/

#include <stdio.h>
#include <stdlib.h>
#include "mendatory/argument.h"

char		*name;

void		usage(void)
{
  printf("USAGE: %s -p port -n name -h machine\n", name);
  printf("       port     is the port number\n");
  printf("       name     is the name of the team\n");
  printf("       machine  is the name of the machine; localhost by default\n");
}

int		arg_entry(int ac, char **av, t_arg *arg)
{
  name = av[0];
  if (ac == 1)
    return (usage(), 1);
  if (help_function(av) == 0)
    return (usage(), 1);
  if (port_function(av, arg) == 1)
    return (1);
  if (name_function(av, arg) == 1)
    return (1);
  if (machine_function(av, arg) == 1)
    return (1);
  return (0);
}

void		arg_free(t_arg *arg)
{
  if (arg->team != NULL)
    free(arg->team);
  if (arg->host != NULL)
    free(arg->host);
  arg->host = NULL;
  arg->host = NULL;
}
