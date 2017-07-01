/*
** eject_func.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:15:03 2017 rodrigue rene
** Last update Wed Jun 28 23:26:16 2017 Gregoire Renard
*/

#include <stdio.h>
#include "server.h"

static int	invert_dir(int dir)
{
  if (dir == 1)
    return (3);
  else if (dir == 3)
    return (1);
  else if (dir == 2)
    return (4);
  else if (dir == 4)
    return (2);
  return (1);
}

static void	eject_a_client(t_client *client, t_pos *dir_p,
			       t_env *env, int dir)
{
  char	buff[11];

  sprintf(buff, "eject: %d\n", invert_dir(dir));
  forward_eject(env, client, dir_p);
  my_send(client, buff, 7 / env->arg.freq);
  g_pex(client, env);
}

static int	eject_each_client(t_env *env, int dir,
				  t_pos *pos_temp, t_pos *dir_p)
{
  int	i;

  i = 0;
  while (env->map[pos_temp->y][pos_temp->x].clients[i] != NULL)
    {
      eject_a_client(env->map[pos_temp->y][pos_temp->x].clients[i],
		     dir_p, env, dir);
      i++;
    }
  return (SUCCESS);
}

int	eject_func(t_env *env, t_client *client, t_list **current)
{
  t_pos	pos;

  (void)current;
  pos.x = client->pos.x;
  pos.y = client->pos.y;
  if (def_dir(client) == 1)
    pos.y--;
  else if (def_dir(client) == 2)
    pos.x++;
  else if (def_dir(client) == 4)
    pos.x--;
  else if (def_dir(client) == 3)
    pos.y++;
  if (pos.y < 0)
    pos.y = env->arg.height - 1;
  else if (pos.x < 0)
    pos.x = env->arg.width - 1;
  else if (pos.x == env->arg.width)
    pos.x = 0;
  else if (pos.y == env->arg.height)
    pos.y = 0;
  eject_each_client(env, def_dir(client), &pos, &client->dir);
  my_send(client, OK, 7 / env->arg.freq);
  return (SUCCESS);
}
