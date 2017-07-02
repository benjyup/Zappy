/*
** f_function.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src/f_function.c
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:20:57 2017 rodrigue rene
** Last update Wed Jun 28 23:21:04 2017 rodrigue rene
*/

#include "server.h"

int		f_pnw(t_env *env, t_client *client_bis, t_list **curent)
{
  t_list                *current;
  t_client              *client;

  (void)client_bis;
  (void)curent;
  current = env->clients->next;
  while (current != env->clients)
    {
      client = current->data;
      if (client->type == player)
	{
	  g_pnw(env, client, curent);
	}
      current = current->next;
    }
  return (SUCCESS);
}
static t_client		*find_client_team(t_env *env, int id_client)
{
  t_list                *current;
  t_client              *client;

  current = env->clients->next;
  while (current != env->clients)
    {
      client = current->data;
      if (client->socket == id_client)
	return (client);
      current = current->next;
    }
  return (NULL);
}

int		f_enw(t_env *env, t_client *client, t_list **current)
{
  int		i;
  t_list	*list_egg;
  t_eggs	*egg;
  t_client	*client_bis;

  i = 0;
  (void)current;
  (void)client;
  while (i < env->arg.nb_team)
    {
      list_egg = env->arg.team[i].eggs->next;
      while (list_egg != env->arg.team[i].eggs)
	{
	  egg = list_egg->data;
	  if (egg != NULL)
	    {
	      client_bis = find_client_team(env, egg->id_client);
	      if (client_bis != NULL)
		g_enw(client_bis, env, egg->id);
	    }
	  list_egg = list_egg->next;
	}
      i++;
    }
  return (1);
}
