/*
** init_new_client.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 18:17:34 2017 Gregoire Renard
** Last update Sun Jul  2 18:00:09 2017 Gregoire Renard
*/

#include "server.h"

void		init_new_client(t_client **client, t_env *env)
{
  (*client)->split_cmd = NULL;
  (*client)->id = env->current_client_id++;
  (*client)->name_team = NULL;
  (*client)->dir.x = 1;
  (*client)->dir.y = 0;
  (*client)->action = 0;
  (*client)->time_unit = -1;
  (*client)->type = none;
  (*client)->incantation = 0;
}
