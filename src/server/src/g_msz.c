/*
** g_msz.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:20:57 2017 rodrigue rene
** Last update Wed Jun 28 23:21:04 2017 Gregoire Renard
*/

#include <stdio.h>
#include "server.h"

int	g_msz(t_env *env, t_client *client, t_list **current)
{
  char	*str;
  char	buff[25];
  int	size;

  (void)current;
  size = sprintf(buff, "%d %d", env->arg.width, env->arg.height);
  size += strlen("msz ");
  size += 3;
  if ((str = malloc(size)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d\n", "msz ", env->arg.width, env->arg.height);
  my_send(client, str, 0);
  free(str);
  return (1);
}

int	bct_f(int x, int y, t_env *env, t_client *client)
{
  int	size;
  char	*str;

  size = get_size_map(x, y, env);
  size += 1;
  size += strlen("bct ");
  if ((str = malloc(size + 1)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d %d %d %d %d %d %d %d\n", "bct ", x, y,
	  env->map[y][x].resource[FOOD],
	  env->map[y][x].resource[LINEMATE],
	  env->map[y][x].resource[DERAUMERE],
	  env->map[y][x].resource[SIBUR],
	  env->map[y][x].resource[MENDIANE],
	  env->map[y][x].resource[PHIRAS],
	  env->map[y][x].resource[THYSTAME]);
  my_send(client, str, 0);
  free(str);
  return (1);
}

int	g_bct(t_env *env, t_client *client, t_list **current)
{
  int	x;
  int	y;

  (void)current;
  if (client->split_cmd[1] == NULL || client->split_cmd[2] == NULL)
    g_sbp(client);
  else
    {
      x = atoi(client->split_cmd[1]);
      y = atoi(client->split_cmd[2]);
      if (x < 0 || y < 0 || y > env->arg.height || x > env->arg.width)
	g_sbp(client);
      else
	bct_f(x, y, env, client);
    }
  return (1);
}

int	g_mct(t_env *env, t_client *client, t_list **current)
{
  int	x;
  int	y;

  x = 0;
  y = 0;
  (void)current;
  while (x < env->arg.width)
    {
      while (y < env->arg.height)
	{
	  bct_f(x, y, env, client);
	  y++;
	}
      y = 0;
      x++;
    }
  return (1);
}

int	g_tna(t_env *env, t_client *client, t_list **current)
{
  int	i;
  char	*str;

  i = 0;
  (void)current;
  while (i < env->arg.nb_team)
    {
      if ((str = malloc(strlen(env->arg.team[i].team_name) + 7)) == NULL)
	{
	  perror(MALLOC);
	  exit(-1);
	}
      sprintf(str, "%s %s\n", "tna ", env->arg.team[i].team_name);
      my_send(client, str, 0);
      free(str);
      i++;
    }
  return (1);
}
