/*
** line_detection.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 19:44:46 2017 Gregoire Renard
** Last update Tue Jun 27 18:58:17 2017 Gregoire Renard
*/

#include "server.h"

void		set_all_pos(t_client *client,
			    t_pos *pos,
			    t_pos *tmp,
			    t_pos *dir)
{
  tmp->x = pos->x;
  tmp->y = pos->y;
  dir->x = 0;
  dir->y = 0;
  if (tmp->x == client->pos.x + 1)
    dir->x = 1;
  else if (tmp->x == client->pos.x - 1)
    dir->x = -1;
  else if (tmp->y == client->pos.y + 1)
    dir->y = 1;
  else if (tmp->y == client->pos.y - 1)
    dir->y = -1;
}

void		line_detection(t_env *env, t_client *client,
			       t_pos *pos, char *message)
{
  t_pos		tmp;
  t_pos		dir;

  set_all_pos(client, pos, &tmp, &dir);
  while (tmp.y != client->pos.y || tmp.x != client->pos.x)
    {
      send_to_all_user(env, tmp, client, message);
      tmp.y += dir.y;
      tmp.x += dir.x;
      if (tmp.x < 0)
        tmp.x = env->arg.width - 1;
      else
        tmp.x = tmp.x % env->arg.width;
      if (tmp.y < 0)
        tmp.y = env->arg.height - 1;
      else
        tmp.y = tmp.y % env->arg.height;
    }
}
