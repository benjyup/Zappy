/*
** init_level6.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 15:38:27 2017 Gregoire Renard
** Last update Sun Jul  2 11:41:01 2017 Gregoire Renard
*/

#include "server.h"

void		init_level6(t_env *env)
{
  int		cpt;

  cpt = 0;
  env->elevation[5].nb_player = 6;
  while (cpt != MAX_RESOURCE)
    {
      env->elevation[5].needed_res[cpt] = 0;
      cpt++;
    }
  env->elevation[5].needed_res[LINEMATE] = 1;
  env->elevation[5].needed_res[DERAUMERE] = 2;
  env->elevation[5].needed_res[SIBUR] = 3;
  env->elevation[5].needed_res[PHIRAS] = 1;
}
