/*
** square_detection.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 20:06:27 2017 Gregoire Renard
** Last update Wed Jun 28 17:58:53 2017 Gregoire Renard
*/

#include "server.h"

static void	set_dir(t_broad *broad, int x, int y)
{
  broad->dir.x = x;
  broad->dir.y = y;
}

static void	init_broad(t_client *client,
			   t_pos *pos, t_broad *broad)
{
  broad->tmp.x = pos->x;
  broad->tmp.y = pos->y;
  if (pos->x == client->pos.x - 1 && pos->y == client->pos.y - 1)
    set_dir(broad, -1, -1);
  else if (pos->x == client->pos.x + 1 && pos->y == client->pos.y - 1)
    set_dir(broad, 1, -1);
  else if (pos->x == client->pos.x - 1 && pos->y == client->pos.y + 1)
    set_dir(broad, -1, 1);
  else if (pos->x == client->pos.x + 1 && pos->y == client->pos.y + 1)
    set_dir(broad, 1, 1);
}

void		square_detection(t_env *env, t_client *client,
				 t_pos *pos, char *message)
{
  t_broad	broad;

  init_broad(client, pos, &broad);
  while (broad.tmp.y >= 0 && broad.tmp.y < env->arg.height)
    {
      while (broad.tmp.x < env->arg.width && broad.tmp.x >= 0)
	{
	  send_to_all_user(env, broad.tmp, client, message);
	  broad.tmp.x += broad.dir.x;
	}
      broad.tmp.x = pos->x;
      broad.tmp.y += broad.dir.y;
    }
}
