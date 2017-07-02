/*
** g_ebo.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 11:40:06 2017 Gregoire Renard
** Last update Sun Jul  2 11:40:07 2017 Gregoire Renard
*/

#include "server.h"

void		g_ebo(t_env *env, int id_egg)
{
  char		buff[32];

  sprintf(buff, "ebo %d\n", id_egg);
  send_graphical(&env->clients->next, env, buff, 0);
}
