/*
** erase_in_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 13:44:57 2017 Gregoire Renard
** Last update Wed Jun 28 23:48:05 2017 Gregoire Renard
*/

#include "server.h"

static void			swap_pointer(t_client *client,
					     int cpt,
					     t_env *env)
{
  while (env->map[client->pos.y][client->pos.x].clients[cpt] != NULL
	 && env->map[client->pos.y][client->pos.x].clients[cpt + 1] != NULL)
    {
      env->map[client->pos.y][client->pos.x].clients[cpt] =
	env->map[client->pos.y][client->pos.x].clients[cpt + 1];
      cpt++;
    }
  env->map[client->pos.y][client->pos.x].clients[cpt] = NULL;
}

static int			strlen_clients(t_client **clients)
{
  int				cpt;

  cpt = 0;
  while (clients[cpt] != NULL)
    cpt++;
  return (cpt);
}

void				erase_in_map(t_env *env,
					     t_client *client)
{
  int				cpt;

  cpt = 0;
  while (env->map[client->pos.y][client->pos.x].clients[cpt] != NULL
	 &&env->map[client->pos.y][client->pos.x].clients[cpt] != client)
    cpt++;
  if (env->map[client->pos.y][client->pos.x].clients[cpt] != NULL)
    swap_pointer(client, cpt, env);
  if ((strlen_clients(env->map[client->pos.y][client->pos.x].clients)) == 0)
    env->map[client->pos.y][client->pos.x].name_team = NULL;
}
