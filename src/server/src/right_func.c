/*
** right_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 16:15:49 2017 Gregoire Renard
** Last update Thu Jun 22 16:17:29 2017 Gregoire Renard
*/

#include "server.h"

int		right_func(t_env *env, t_client *client,
			   t_list **current)
{
  (void)env;
  (void)current;
  if (client->dir.x == 1)
    {
      client->dir.x = 0;
      client->dir.y = 1;
    }
  else if (client->dir.y == -1)
    {
      client->dir.x = 1;
      client->dir.y = 0;
    }
  else if (client->dir.x == -1)
    {
      client->dir.x = 0;
      client->dir.y = -1;
    }
  else if (client->dir.y == 1)
    {
      client->dir.x = -1;
      client->dir.y = 0;
    }
  my_send(client, OK);
  return (SUCCESS);
}
