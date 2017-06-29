/*
** my_zappy_server.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 26 14:57:15 2017 vincent.mesquita@epitech.eu
** Last update Thu Jun 29 16:49:07 2017 Gregoire Renard
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

static t_bool           my_new_client(int client_socket,
				      t_env *env)
{
  t_client              *client;

  if (!(client = malloc(sizeof(*client))) ||
      !(client->to_write = my_init_list()))
    {
      perror(MALLOC);
      exit(ERROR);
    }
  if (client_socket > env->highest_fd)
    env->highest_fd = client_socket;
  client->socket = client_socket;
  memset(client->cmd, 0, BUFFLENGTH);
  client->split_cmd = NULL;
  client->id = env->current_client_id++;
  client->name_team = NULL;
  client->dir.x = 1;
  client->dir.y = 0;
  client->action = 0;
  my_add_to_end(env->clients, client);
  my_send(client, WELCOME, 0);
  env->nb_player++;
  return (true);
}

static t_bool            my_get_client_cmd(t_env *env,
					   t_list **current,
					   t_client *client)
{
  ssize_t		n;
  int			i;

  i = 0;
  while ((n = read(client->socket, &client->cmd[i], 1)) == 1 &&
	 client->cmd[i] != END_OF_CMD &&
	 i < BUFFLENGTH)
    i += 1;
  if (n <= 0)
    {
      my_quit(env, client, current);
      printf("CLIENT DECONNECTEE\n");
      return (false);
    }
  client->cmd[i] = 0;
  fprintf(stderr, "client%lu : %s\n", client->id, client->cmd);
  return (true);
}

static void             my_check_each_client(t_env *env)
{
  t_list                *current;
  t_client              *client;

  current = env->clients->next;
  while (current != env->clients)
    {
      client = current->data;
      pop_food(env);
      if (FD_ISSET(client->socket, &(env->readf)))
	{
	  client = current->data;
	  client->this = current;
	  if (!my_get_client_cmd(env, &current, client))
	    continue ;
	  if (client->name_team == NULL)
	    know_team(env, client);
	  else
	    my_exec(env, client, &current);
	  print_map(env);
	}
      if (FD_ISSET(client->socket, &(env->writef)))
	my_send_to_client(client);
      current = current->next;
    }
}

t_bool			my_zappy_server(t_env *env)
{
  struct sockaddr_in    client_sin;
  unsigned int          client_sin_len;
  int                   client_socket;

  client_sin_len = sizeof(client_sin);
  while (42)
    {
      my_init_select(env);
      if (my_select(env->highest_fd + 1, &(env->readf), &(env->writef)) == -1)
	return (false);
      if (FD_ISSET(env->socket, &(env->readf)))
	{
	  fprintf(stderr, "new client !\n");
	  if ((client_socket = accept(env->socket,
				      (struct sockaddr *)&client_sin,
				      &client_sin_len)) == -1)
	    return (false);
	  my_new_client(client_socket, env);
	}
      my_check_each_client(env);
    }
  return (true);
}
