/*
** fork_func.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:14:47 2017 rodrigue rene
** Last update Wed Jun 28 23:27:26 2017 Gregoire Renard
*/

#include "server.h"

int     fork_func(t_env *env, t_client *client, t_list **current)
{
  (void)env;
  (void)current;
  //ajouter un egg
  my_send(client, OK, 42 / env->arg.freq);
  return (SUCCESS);
}
