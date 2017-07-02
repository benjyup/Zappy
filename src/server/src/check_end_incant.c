/*
** check_end_incant.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 19:11:39 2017 Gregoire Renard
** Last update Sun Jul  2 22:01:08 2017 Gregoire Renard
*/

#include "server.h"

static int	strlen_clients(t_client **client)
{
  int		cpt;

  cpt = 0;
  while (client[cpt] != NULL)
    cpt++;
  return (cpt);
}

int		check_end_incante(t_env *env, t_client *client)
{
  int		nb_player;
  int		cpt;
  int		stop;

  cpt = 1;
  stop = 0;
  nb_player = strlen_clients(env->map[client->pos.y][client->pos.x].clients);
  if (nb_player != env->elevation[client->level - 1].nb_player)
    return (ERROR);
  while (cpt != MAX_RESOURCE && stop != 1)
    {
      if (env->map[client->pos.y][client->pos.x].resource[cpt]
	  != env->elevation[client->level - 1].needed_res[cpt])
	stop = 1;
      cpt++;
    }
  if (stop == 1)
    return (ERROR);
  else
    return (SUCCESS);
}

void		up_all_player(t_env *env, t_client *client)
{
  int		cpt;

  cpt = 0;
  g_pie(env, client, &env->clients->next, 1);
  while (env->map[client->pos.y][client->pos.x].clients[cpt] != NULL)
    {
      if (env->map[client->pos.y][client->pos.x].clients[cpt]->level
	  == client->level - 1
	  && env->map[client->pos.y][client->pos.x].clients[cpt] != client)
	{
	  g_plv(env, client, &env->clients->next);
	  env->map[client->pos.y][client->pos.x].clients[cpt]->level++;
	}
      cpt++;
    }
}
