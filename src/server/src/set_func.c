/*
** set_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 15:22:21 2017 Gregoire Renard
** Last update Wed Jun 28 23:10:59 2017 Gregoire Renard
*/

#include "server.h"

static void	put_object(t_env *env, t_client *client,
			   int cpt)
{
  if (client->inventory[cpt] >= 1)
    {
      client->inventory[cpt]--;
      env->map[client->pos.y][client->pos.x].resource[cpt]++;
      my_send(client, OK, 7 / env->arg.freq);
      g_pdr(env, client, &env->clients->next, cpt);
    }
  else
    my_send(client, KO, 7 / env->arg.freq);
}

int		set_func(t_env *env, t_client *client,
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
	put_object(env, client, cpt);
      else
	my_send(client, KO, 7 / env->arg.freq);
    }
  else
    my_send(client, KO, 7 / env->arg.freq);
  return (SUCCESS);
}

void		send_graphical(t_list **current, t_env *env, char *str, int time)
{
  t_list	*tmp;
  t_client	*client_temp;
  int		i;

  i = 0;
  tmp = *current;
  while (i < env->nb_player)
    {
      client_temp = tmp->data;
      if (client_temp->type == monitor)
	my_send(client_temp, str, time);
      tmp = tmp->next;
      i++;
    }
}
