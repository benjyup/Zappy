/*
** server.c for  in /home/vincent/rendu/MyIRC/PSU_2016_myirc/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon May 29 17:40:11 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 17:12:59 2017 Gregoire Renard
*/

#include <netdb.h>
#include "server.h"

static t_bool		my_init_server2(t_env *env)
{
  memset(&(env->info), 0, env->struct_length);
  env->info.sin_family = AF_INET;
  env->info.sin_addr.s_addr = INADDR_ANY;
  env->info.sin_port = htons(env->arg.port);
  env->current_client_id = 0;
  env->time_food = time(NULL);
  if (!(env->clients = my_init_list()))
    return (false);
  return (true);
}

t_bool			init_server(t_env *env)
{
  if (env->arg.port <= 0)
    {
      fprintf(stderr, "Port must be superior to 0\n");
      return (false);
    }
  env->struct_length = sizeof(env->info);
  if (!(env->pe = getprotobyname(SOCKET_PROTOCOL)) ||
      (env->socket = socket(AF_INET,
			    SOCK_STREAM,
			    env->pe->p_proto)) == -1)
    {
      perror("Error");
      return (false);
    }
  env->highest_fd = env->socket;
  if (!my_init_server2(env) || bind(env->socket,
				    (struct sockaddr *)&(env->info),
				    env->struct_length) < 0 ||
      listen(env->socket, 5) != 0)
    {
      perror("Error");
      return (false);
    }
  return (true);
}
