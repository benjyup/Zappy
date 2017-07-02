/*
** g_function1.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:16:12 2017 rodrigue rene
** Last update Wed Jun 28 23:22:03 2017 Gregoire Renard
*/

#include <stdio.h>
#include "server.h"

int		g_pdi(t_client *client, t_env *env)
{
  char		buff[32];

  sprintf(buff, "pdi %d\n", client->socket);
  send_graphical(&env->clients->next, env, buff, 0);
  return (SUCCESS);
}
