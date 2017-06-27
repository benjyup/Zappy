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

static void	eject_a_client(t_client *client, t_pos *dir_p, t_env *env, int dir)
{
  char	buff[10];
  
  sprintf(buff, "eject: %d", invert_dir(dir));
  forward_eject(env, client, dir_p);
  my_send(client, buff);
}

static int	eject_each_client(t_env *env, int dir, t_pos *pos_temp, t_pos *dir_p)
{
  int	i;

  i = 0;
  while (env->map[pos_temp->y][pos_temp->x].clients[i] != NULL)
    {
      eject_a_client(env->map[pos_temp->y][pos_temp->x].clients[i], dir_p, env, dir);
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
  if (pos.y < 0)
    pos.y = env->arg.height - 1;
  if (pos.x < 0)
    pos.x = env->arg.width - 1;
  if (pos.x == env->arg.width)
    pos.x = 0;
  eject_each_client(env, def_dir(client), &pos, &client->dir);
  my_send(client, OK);
  return (SUCCESS);
}
