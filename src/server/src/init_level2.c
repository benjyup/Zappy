/*
** init_level2.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 15:30:20 2017 Gregoire Renard
** Last update Fri Jun 30 15:31:45 2017 Gregoire Renard
*/

#include "server.h"

void		init_level2(t_env *env)
{
  int		cpt;

  cpt = 0;
  env->elevation[1].nb_player = 2;
  while (cpt != MAX_RESOURCE)
    {
      env->elevation[1].needed_res[cpt] = 0;
      cpt++;
    }
  env->elevation[1].needed_res[LINEMATE] = 1;
  env->elevation[1].needed_res[DERAUMERE] = 1;
  env->elevation[1].needed_res[SIBUR] = 1;
}
