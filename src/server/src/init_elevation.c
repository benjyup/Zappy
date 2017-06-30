/*
** init_elevation.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 15:25:01 2017 Gregoire Renard
** Last update Fri Jun 30 15:26:58 2017 Gregoire Renard
*/

#include "server.h"

void		init_elevation(t_env *env)
{
  init_level1(env);
  init_level2(env);
  init_level3(env);
  init_level4(env);
  init_level5(env);
  init_level6(env);
  init_level7(env);
}
