/*
** my_quit.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:28:44 2017 vincent.mesquita@epitech.eu
** Last update Wed Jun 21 18:09:49 2017 Gregoire Renard
*/

#include "server.h"

void				erase_in_map(t_env *env,
					     t_client *client)
{
  int				cpt;
  int				active;
  
  cpt = 0;
  active = 0;
  while (env->map[client->pos.y][client->pos.x].fd_player[cpt]
	 != client->socket)
    cpt++;
  env->map[client->pos.y][client->pos.x].fd_player[cpt] = -1;
  cpt = 0;
  while (cpt != env->arg.clients_lim &&
	 env->map[client->pos.y][client->pos.x].fd_player[cpt]
	 != -1)
    {
      if (env->map[client->pos.y][client->pos.x].fd_player[cpt]
	  != -1)
	active = 1;
      cpt++;
    }
  if (active == 0)
    env->map[client->pos.y][client->pos.x].name_team = NULL;
}

int                             my_quit(t_env *env,
					t_client *client,
					t_list **current)
{
  t_list                        *prev;

  (void)current;
  erase_in_map(env, client);
  my_close(client, env);
  prev = (*current)->prev;
  my_del_elem(env->clients, *current, NULL); //doit pas être NULL
  *current = prev;
  return (SUCCESS);
}
