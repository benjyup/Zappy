/*
** srv_read.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/src/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 20:50:23 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:07:39 2017 vincent.mesquita@epitech.eu
*/

#include <string.h>
#include <zconf.h>
#include <printf.h>
#include <stdio.h>
#include "mendatory/my_stack.h"

static t_stack	*rs = NULL;

char		*srv_read(void)
{
  char		*s;

  if (rs == NULL)
    return (NULL);
  if (!(s = strdup(rs->data)))
    return (perror("strdup()"), NULL);
  rs = stack_delete(rs);
  return (s);
}

int		server_download_data(int fd)
{
  char		data[512];
  char		*s;

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
