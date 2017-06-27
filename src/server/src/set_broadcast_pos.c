/*
** set_broadcast_pos.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 09:09:52 2017 Gregoire Renard
** Last update Mon Jun 26 20:20:12 2017 Gregoire Renard
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

void		set_broadcast_pos(t_env *env,
				  t_client *client,
				  t_pos *pos,
				  char *message)
{
  if (pos->x == client->pos.x && pos->y == client->pos.y)
    {
      pos->x += client->dir.x;
      pos->y += client->dir.y;
    }
  else
    right_turn(client, pos);
  if ((pos->x == client->pos.x + 1 && pos->y == client->pos.y)
      || (pos->x == client->pos.x - 1 && pos->y == client->pos.y)
      || (pos->x == client->pos.x && pos->y == client->pos.y - 1)
      || (pos->x == client->pos.x && pos->y == client->pos.y + 1))
    line_detection(env, client, pos, message);
  else
    square_detection(env, client, pos, message);
}
