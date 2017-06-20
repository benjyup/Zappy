/*
** my_quit.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:28:44 2017 vincent.mesquita@epitech.eu
** Last update Mon Jun 19 22:31:33 2017 vincent.mesquita@epitech.eu
*/

#include "server.h"

int                             my_quit(t_env *env,
					t_client *client,
					t_list **current)
{
  t_list                        *prev;

  (void)current;
  my_close(client, env);
  prev = (*current)->prev;
  my_del_elem(env->clients, *current, NULL); //doit pas être NULL
  *current = prev;
  return (SUCCESS);
}
