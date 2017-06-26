/*
** set_broadcast_pos.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 09:09:52 2017 Gregoire Renard
** Last update Mon Jun 26 17:43:33 2017 Gregoire Renard
*/

#include "server.h"

static void	right_turn(t_client *client,
			   t_pos *pos)
{
  if ((pos->x == client->pos.x + 1 && pos->y == client->pos.y)
      || (pos->x == client->pos.x + 1 && pos->y == client->pos.y + 1))
    pos->y--;
  else if ((pos->x == client->pos.x + 1 && pos->y == client->pos.y - 1)
	   || (pos->x == client->pos.x && pos->y == client->pos.y - 1))
    pos->x--;
  else if ((pos->x == client->pos.x - 1 && pos->y == client->pos.y - 1)
	   || (pos->x == client->pos.x - 1 && pos->y == client->pos.y))
    pos->y++;
  else if ((pos->x == client->pos.x - 1 && pos->y == client->pos.y + 1)
	   || (pos->x == client->pos.x && pos->y == client->pos.y + 1))
    pos->x++;
}

t_pos		set_broadcast_pos(t_env *env,
				  t_client *client,
				  t_pos *pos,
				  int decale)
{
  t_pos		tmp;

  printf("client->dir.x = %i, client->dir.y = %i\n", client->dir.x, client->dir.y);
  if (decale == 1)
    {
      pos->x += client->dir.x;
      pos->y += client->dir.y;
    }
  right_turn(client, pos);
  tmp.x = pos->x;
  tmp.y = pos->y;  
  if (tmp.x < 0)
    tmp.x = env->arg.width - 1;
  else
    tmp.x = tmp.x % env->arg.width;
  if (tmp.y < 0)
    tmp.y = env->arg.height - 1;
  else
    tmp.y = tmp.y % env->arg.height;
  return (tmp);
}
