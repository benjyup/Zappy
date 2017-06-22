/*
** erase_in_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 13:44:57 2017 Gregoire Renard
** Last update Thu Jun 22 15:03:10 2017 Gregoire Renard
*/

#include "server.h"

void				erase_in_map(t_env *env,
					     t_client *client)
{
  int				cpt;
  int				active;
  
  cpt = 0;
  active = 0;
  while (cpt != env->arg.clients_lim &&
	 env->map[client->pos.y][client->pos.x].fd_player[cpt]
	 != client->socket)
    cpt++;
  if (cpt != env->arg.clients_lim)
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
