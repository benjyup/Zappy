/*
** add_in_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 14:01:23 2017 Gregoire Renard
** Last update Thu Jun 22 14:53:28 2017 Gregoire Renard
*/

#include "server.h"

void			add_in_map(t_env *env, t_client *client)
{
  int			cpt;

  cpt = 0;
  if (env->map[client->pos.y][client->pos.x].name_team == NULL)
    env->map[client->pos.y][client->pos.x].name_team = client->name_team;
  while (env->map[client->pos.y][client->pos.x].fd_player[cpt] != -1)
    cpt++;
  env->map[client->pos.y][client->pos.x].fd_player[cpt] = client->socket;
}
