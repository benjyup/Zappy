/*
** check_end_game.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 17:21:31 2017 Gregoire Renard
** Last update Sun Jul  2 11:39:50 2017 Gregoire Renard
*/

#include "server.h"

static int	lets_start_game(t_env *env)
{
  int		cpt;
  int		dif;

  cpt = 0;
  dif = 0;
  while (cpt != env->arg.nb_team)
    {
      if (env->arg.team[cpt].nb_player != 0)
	dif++;
      cpt++;
    }
  if (dif >= 2)
    return (SUCCESS);
  return (ERROR);
}

static int	check_team_alive(t_env *env)
{
  int		cpt;
  int		alive;

  cpt = 0;
  alive = 0;
  while (cpt != env->arg.nb_team)
    {
      if (env->arg.team[cpt].nb_player != 0)
	alive++;
      cpt++;
    }
  return (alive);
}

static char	*who_is_winner(t_env *env)
{
  int		cpt;

  cpt = 0;
  while (cpt != env->arg.nb_team)
    {
      if (env->arg.team[cpt].nb_player != 0)
	return (env->arg.team[cpt].team_name);
      cpt++;
    }
  return (NULL);
}

void		check_end_game(t_env *env)
{
  if (env->real_start == 0)
    {
      if ((lets_start_game(env)) == SUCCESS)
	env->real_start = 1;
    }
  else
    if ((check_team_alive(env)) == 1 && env->real_start != 0)
      g_seg(env, who_is_winner(env));
}
