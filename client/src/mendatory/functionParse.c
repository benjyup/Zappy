//
// Created by Jean-Adrien on 19/06/17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mendatory/argument.h"

int help_function(char **av)
{
  int i;

  i = 0;
  while (av[i])
    {
      if (strcmp(av[i], "-help") == 0)
	return (0);
      i += 1;
    }
  return (1);
}

int port_function(char **av, t_arg *arg)
{
  int i;
  char *endptr;

  i = 0;
  while (av[i])
    {
      if (strcmp(av[i], "-p") == 0)
	{
	  if (!av[i + 1] || av[i + 1][0] == '\0')
	    return (1);
	  arg->port = strtol(av[i + 1], &endptr, 10);
	  if (endptr[0] != '\0')
	    return (printf("%s: Invalide port.\n", name), 1);
	  return (0);
	}
      i += 1;
    }
  return (usage(), 1);
}

int name_function(char **av, t_arg *arg)
{
  int i;

  i = 0;
  while (av[i])
    {
      if (strcmp(av[i], "-n") == 0)
	{
	  if (!av[i + 1] || av[i + 1][0] == '\0')
	    return (usage(), 1);
	  arg->team = strdup(av[i + 1]);
	  return (0);
	}
      i += 1;
    }
  return (usage(), 1);
}

int machine_function(char **av, t_arg *arg)
{
  int i;

  i = 0;
  while (av[i])
    {
      if (strcmp(av[i], "-h") == 0)
	{
	  if (!av[i + 1] || av[i + 1][0] == '\0')
	    return (usage(), 1);
	  if (strcmp(av[i + 1], "localhost") == 0)
	    arg->host = strdup("127.0.0.1");
	  else
	    arg->host = strdup(av[i + 1]);
	  return (0);
	}
      i += 1;
    }
  arg->host = strdup("127.0.0.1");
  return (0);
}