/*
** my_select.c for  in /home/vincent/rendu/MyIRC/PSU_2016_myirc/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Tue May 30 16:56:52 2017 vincent.mesquita@epitech.eu
** Last update Thu Jun 29 14:07:18 2017 Gregoire Renard
*/

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"

int		my_select(int nfds,
			  fd_set *readfds,
			  fd_set *writefds)
{
  int		ret;

  if ((ret = select(nfds, readfds, writefds, NULL, NULL)) == -1)
    {
      perror("select");
      return (ret);
    }
  return (ret);
}

void		my_init_select(t_env *env)
{
  t_list	*current;
  t_client	*client;

  FD_ZERO(&(env->readf));
  FD_ZERO(&(env->writef));
  FD_SET(env->socket, &(env->readf));
  current = env->clients->next;
  while (current != env->clients)
    {
      client = current->data;
      if (client->socket > env->highest_fd)
	env->highest_fd = client->socket;
      if (client->action != 1)
	FD_SET(client->socket, &(env->readf));
      FD_SET(client->socket, &(env->writef));
      current = current->next;
    }
}
