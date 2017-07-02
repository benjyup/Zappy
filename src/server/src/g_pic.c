/*
** g_pnw.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:21:28 2017 rodrigue rene
** Last update Tue Jun 27 19:28:58 2017 rodrigue rene
*/

#include "server.h"

static void	fill_pic(char **buff, t_env *env, t_client *client)
{
  char		tmp[12];
  int		i;

  i = 0;
  while (env->map[client->pos.y][client->pos.x].clients[i] != NULL)
    {
      if (client->socket !=
	  env->map[client->pos.y][client->pos.x].clients[i]->socket)
	{
	  sprintf(tmp, " %d",
		  env->map[client->pos.y][client->pos.x].clients[i]->socket);
	  *buff = strcat(*buff, tmp);
	}
      i++;
    }
  *buff = strcat(*buff, "\n");
}

int	g_pic(t_env *env, t_client *client, t_list **current)
{
  char	*buff;

  if ((buff = malloc(1024)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(buff, "pic %d %d %d %d", client->pos.x, client->pos.y,
	  client->level, client->socket);
  fill_pic(&buff, env, client);
  send_graphical(current, env, buff, 0);
  return (1);
}

int	g_pie(t_env *env, t_client *client, t_list **current, int res)
{
  char	buff[64];

  sprintf(buff, "pie %d %d %d\n", client->pos.x, client->pos.y, res);
  send_graphical(current, env, buff, 0);
  return (1);
}
