/*
** init_level7.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 15:51:18 2017 Gregoire Renard
** Last update Fri Jun 30 15:52:32 2017 Gregoire Renard
*/

#include "server.h"

void		init_level7(t_env *env)
{
  int		cpt;

  cpt = 0;
  env->elevation[6].nb_player = 6;
  while (cpt != MAX_RESOURCE)
    {
      env->elevation[6].needed_res[cpt] = 2;
      cpt++;
    }
  env->elevation[6].needed_res[THYSTAME] = 1;
}
