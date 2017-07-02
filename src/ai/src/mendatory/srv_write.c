/*
** srv_write.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/src/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 20:50:20 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:08:05 2017 vincent.mesquita@epitech.eu
*/

#include <zconf.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mendatory/my_stack.h"

static t_stack	*ws = NULL;

int 		srv_write(const char *s)
{
  char 		*str;

  if (!(str = malloc(strlen(s) + 2)) ||
      !strcpy(str, s) || !strcat(str, "\n"))
    return (-1);

  if (!(ws = stack_new(ws, str)))
    {

      return (-1);
    }
  return (0);
}

int		server_upload_data(int fd)
{
  int		ret;
  int		size;

  if (ws != NULL && ws->data != NULL)
    {
      size = strlen(ws->ptr);
      if ((ret = write(fd, ws->ptr, size)) == -1)
	{

	  return (perror("write()"), 1);
	}
      if (ret != size)
	{
	  ws->ptr += ret;

	  return (0);
	}
      ws = stack_delete(ws);
    }

  return (0);
}
