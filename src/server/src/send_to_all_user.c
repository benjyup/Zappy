/*
** send_to_all_user.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 19:54:39 2017 Gregoire Renard
** Last update Wed Jun 28 23:04:54 2017 Gregoire Renard
*/

#include "server.h"

void		send_to_all_user(t_env *env, t_pos pos,
				 t_client *client, char *message)
{
  int		cpt;

  cpt = 0;
  while (env->map[pos.y][pos.x].clients[cpt] != NULL)
    {
      if (env->map[pos.y][pos.x].clients[cpt] != client)
	my_send(env->map[pos.y][pos.x].clients[cpt], message, 0);
      cpt++;
    }
}
