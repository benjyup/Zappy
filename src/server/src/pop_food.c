/*
** pop_food.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 29 16:49:19 2017 Gregoire Renard
** Last update Thu Jun 29 17:19:57 2017 Gregoire Renard
*/

#include "server.h"

static void	create_food(t_env *env)
{
  t_pos		pos;

  pos.x = rand() % env->arg.width;
  pos.y = rand() % env->arg.height;
  env->map[pos.y][pos.x].resource[FOOD]++;
}

void		pop_food(t_env *env)
{
  int		cpt;

  cpt = 0;
  if (time(NULL) - env->time_food >= 15)
    {
      env->time_food = time(NULL);
      while (cpt < env->nb_player)
	{
	  create_food(env);
	  cpt++;
	}
    }
}
