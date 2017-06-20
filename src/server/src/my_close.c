/*
** my_close.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:27:43 2017 vincent.mesquita@epitech.eu
** Last update Mon Jun 19 22:29:10 2017 vincent.mesquita@epitech.eu
*/

#include <unistd.h>
#include "server.h"

void            my_close(t_client *client, t_env *env)
{
  t_list        *current;
  t_client      *c;
  int           highest_fd;

  current = env->clients->next;
  highest_fd = -1;
  while (current != env->clients)
    {
      c = current->data;
      if (c->socket > highest_fd && c->socket != client->socket)
	highest_fd = c->socket;
      if (c->id == client->id)
	(void)close(client->socket);
      current = current->next;
    }
  env->highest_fd = ((highest_fd < env->socket) ?
		     (env->socket) : (highest_fd));
}
