/*
** my_quit.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:28:44 2017 vincent.mesquita@epitech.eu
** Last update Mon Jun 26 14:47:48 2017 Gregoire Renard
*/

#include "server.h"

static void			find_team(t_env *env,
					  t_client *client)
{
  int				cpt;

  cpt = 0;
  while (cpt != env->arg.nb_team &&
	 (strcmp(env->arg.team[cpt].team_name, client->name_team)) != 0)
    cpt++;
  if (cpt != env->arg.nb_team)
    env->arg.team[cpt].nb_player--;
}

int                             my_quit(t_env *env,
					t_client *client,
					t_list **current)
{
  t_list                        *prev;

  (void)current;
  if (client->name_team != NULL && client->type != monitor)
    {
      erase_in_map(env, client);
      find_team(env, client);
    }
  my_close(client, env);
  prev = (*current)->prev;
  my_del_elem(env->clients, *current, NULL);
  *current = prev;
  env->nb_player--;
  return (SUCCESS);
}
