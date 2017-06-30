/*
** fork_func.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:14:47 2017 rodrigue rene
** Last update Wed Jun 28 23:53:39 2017 Gregoire Renard
*/

#include "server.h"

static void	put_egg(t_env *env, t_client *client)
{
  int		i;
  t_eggs        *egg;

  i = 0;
  if ((egg = malloc(sizeof(t_eggs))) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  while (i < env->arg.nb_team)
    {
      if (!strcmp(client->name_team, env->arg.team[i].team_name))
	{
	  egg->pos.x = client->pos.x;
	  egg->pos.y = client->pos.y;
	  my_add_to_end(env->arg.team[i].eggs, egg);
	  env->nb_eggs++;
	  egg->id = env->nb_eggs;
	  i = env->arg.nb_team;
	}
      i++;
    }
}

int		fork_func(t_env *env, t_client *client, t_list **current)
{
  (void)current;
  put_egg(env, client);
  env->nb_eggs++;
  g_pfk(client, env);
  g_enw(client, env, env->nb_eggs);
  g_eht(client, env, env->nb_eggs);
  my_send(client, OK, 42 / env->arg.freq);
  return (SUCCESS);
}
