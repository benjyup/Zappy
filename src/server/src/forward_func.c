/*
** forward_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 12:14:34 2017 Gregoire Renard
** Last update Thu Jun 22 15:31:35 2017 Gregoire Renard
*/

#include "server.h"

static void	set_new_pos(t_env *env, t_client *client,
			    t_pos *new_pos)
{
  new_pos->x = client->pos.x + client->dir.x;
  new_pos->y = client->pos.y + client->dir.y;
  if (new_pos->x < 0)
    new_pos->x = env->arg.width - 1;
  if (new_pos->y < 0)
    new_pos->y = env->arg.height - 1;
  if (new_pos->y >= env->arg.height)
    new_pos->y = 0;
  if (new_pos->x >= env->arg.width)
    new_pos->x = 0;
}

int		forward_func(t_env *env, t_client *client,
			     t_list **current)
{
  t_pos		new_pos;

  (void)current;
  set_new_pos(env, client, &new_pos);
  if (env->map[new_pos.y][new_pos.x].name_team == NULL
      || (env->map[new_pos.y][new_pos.x].name_team != NULL
	  && (strcmp(env->map[new_pos.y][new_pos.x].name_team,
		     client->name_team)) == 0))
    {
      erase_in_map(env, client);
      client->pos.y = new_pos.y;
      client->pos.x = new_pos.x;
      add_in_map(env, client);
      my_send(client, OK);
    }
  else
    my_send(client, KO);
  return (SUCCESS);
}
