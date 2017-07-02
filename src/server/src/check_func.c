/*
** check_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 29 18:15:04 2017 Gregoire Renard
** Last update Sun Jul  2 18:50:03 2017 Gregoire Renard
*/

#include "server.h"

void		check_func(t_env *env, t_client *client,
			   t_list **current)
{
  check_timer_client(env, client, current);
}
