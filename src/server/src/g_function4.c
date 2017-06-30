/*
** g_function4.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:17:32 2017 rodrigue rene
** Last update Wed Jun 28 23:24:51 2017 Gregoire Renard
*/

#include <stdio.h>
#include "server.h"

int	get_size_map(int x, int y, t_env *env)
{
  char	buff[13];
  int	size;

  size = sprintf(buff, " %d", env->map[y][x].resource[FOOD]);
  size += sprintf(buff, " %d", env->map[y][x].resource[LINEMATE]);
  size += sprintf(buff, " %d", env->map[y][x].resource[DERAUMERE]);
  size += sprintf(buff, " %d", env->map[y][x].resource[SIBUR]);
  size += sprintf(buff, " %d", env->map[y][x].resource[MENDIANE]);
  size += sprintf(buff, " %d", env->map[y][x].resource[PHIRAS]);
  size += sprintf(buff, " %d", env->map[y][x].resource[THYSTAME]);
  size += sprintf(buff, " %d", x);
  size += sprintf(buff, " %d", y);
  return (size);
}

int		g_ppo(t_env *env, t_client *client, t_list **current)
{
  t_client	*cli_temp;
  char		buff[33];
  char		*str;
  int		size;
  int		dir;
  int		n;

  (void)env;
  if (client->split_cmd[1] == NULL)
    {
      g_sbp(client);
      return (1);
    }
  n = atoi(client->split_cmd[1]);
  cli_temp = search_client(current, n, env);
  size = sprintf(buff, "%d%d%d\n", n, cli_temp->pos.x, cli_temp->pos.y);
  size += 5;
  dir = def_dir(cli_temp);
  str = malloc(size + 1);
  sprintf(str, "%s %d %d %d %d\n", "ppo ", n,
	  cli_temp->pos.x, cli_temp->pos.y, dir);
  my_send(client, str, 0);
  free(str);
  return (1);
}

int		g_plv(t_env *env, t_client *client, t_list **current)
{
  t_client	*cli_temp;
  char		*str;
  char		buff[13];
  int		size;
  int		n;

  (void)env;
  if (client->split_cmd[1] == NULL)
    {
      g_sbp(client);
      return (1);
    }
  n = atoi(client->split_cmd[1]);
  cli_temp = search_client(current, n, env);
  size = sprintf(buff, "%d\n", n);
  if ((str = malloc(size + 7)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d\n", "plv ", n, cli_temp->level);
  my_send(client, str, 0);
  free(str);
  return (1);
}

int		g_pin(t_env *env, t_client *client, t_list **current)
{
  t_client	*cli_temp;
  char		*str;
  int		size;

  if (client->split_cmd[1] == NULL)
    {
      g_sbp(client);
      return (1);
    }
  cli_temp = search_client(current, atoi(client->split_cmd[1]), env);
  size = get_size(cli_temp, atoi(client->split_cmd[1]));
  if ((str = malloc(size + 4)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d %d %d %d %d %d %d %d %d\n", "pin ",
	  atoi(client->split_cmd[1]),
	  cli_temp->pos.x, cli_temp->pos.y, cli_temp->inventory[FOOD],
	  cli_temp->inventory[LINEMATE], cli_temp->inventory[DERAUMERE],
	  cli_temp->inventory[SIBUR], cli_temp->inventory[MENDIANE],
	  cli_temp->inventory[PHIRAS], cli_temp->inventory[THYSTAME]);
  my_send(client, str, 0);
  free(str);
  return (1);
}
