/*
** winner_function.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 17:47:10 2017 Gregoire Renard
** Last update Sun Jul  2 18:25:06 2017 Gregoire Renard
*/

#include "server.h"

t_bool			winner_function(t_env *env,
					char *team)
{
  g_seg(env, team);
  return (true);
}
