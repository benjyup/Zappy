/*
** take_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 15:54:45 2017 Gregoire Renard
** Last update Wed Jun 28 23:06:53 2017 Gregoire Renard
*/

#include "server.h"

static void	grep_object(t_env *env, t_client *client,
			    int cpt)
{
  if (env->map[client->pos.y][client->pos.x].resource[cpt] >= 1)
    {
      env->map[client->pos.y][client->pos.x].resource[cpt]--;
      client->inventory[cpt]++;
      g_pgt(env, client, &env->clients->next, cpt);
      my_send(client, OK, 7 / env->arg.freq);
    }
  else
    my_send(client, KO, 7 / env->arg.freq);
}

int		take_func(t_env *env, t_client *client,
			  t_list **current)
{
  int		cpt;

  (void)current;
  if (client->split_cmd[1] != NULL)
    {
      cpt = 0;
      while (env->resources[cpt] != NULL &&
	     (strcmp(env->resources[cpt],
		     client->split_cmd[1])) != 0)
	cpt++;
      if (env->resources[cpt] != NULL)
	grep_object(env, client, cpt);
      else
	my_send(client, KO, 7 / env->arg.freq);
    }
  else
    my_send(client, KO, 7 / env->arg.freq);
  return (SUCCESS);
}
