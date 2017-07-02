/*
** pop_food.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 29 16:49:19 2017 Gregoire Renard
** Last update Sun Jul  2 18:51:04 2017 Gregoire Renard
*/

#include "server.h"

static void	create_food(t_env *env)
{
  t_pos		pos;
  int		cpt;

  cpt = 0;
  pos.x = rand() % env->arg.width;
  pos.y = rand() % env->arg.height;
  while (cpt != 5)
    {
      env->map[pos.y][pos.x].resource[FOOD]++;
      cpt++;
    }
}

void		pop_food(t_env *env)
{
  int		cpt;

  cpt = 0;
  env->time_food = time(NULL);
  while (cpt < env->nb_player)
    {
      create_food(env);
      cpt++;
    }
}
