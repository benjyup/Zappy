#include <stdio.h>
#include "commands.h"

int	g_msz(t_env *env, t_client *client, t_list **current)
{
  char	*str;
  char	buff[25];
  int	size;
  
  (void)current;
  size = sprintf(buff, "%d%d", env->arg.width, env->arg.height);
  size += strlen(MSZ);
  size += 3;
  if ((str = malloc(size)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d\n", MSZ, env->arg.width, env->arg.height);
  my_send(client, str);
  free(str);
  return (1);
}

int	bct_f(int x, int y, t_env *env, t_client *client)
{
  int	size;
  char	*str;
  char	buff[13];

  (void)client;
  size = sprintf(buff, " %d", env->map[y][x].resource[FOOD]);
  size += sprintf(buff, " %d", env->map[y][x].resource[LINEMATE]);
  size += sprintf(buff, " %d", env->map[y][x].resource[DERAUMERE]);
  size += sprintf(buff, " %d", env->map[y][x].resource[SIBUR]);
  size += sprintf(buff, " %d", env->map[y][x].resource[MENDIANE]);
  size += sprintf(buff, " %d", env->map[y][x].resource[PHIRAS]);
  size += sprintf(buff, " %d", env->map[y][x].resource[THYSTAME]);
  size += sprintf(buff, "%d", x);
  size += sprintf(buff, "%d", y);
  size += 1;
  size += strlen(BCT);
  str = malloc(size + 1);
  sprintf(str, "%s %d %d %d %d %d %d %d %d %d\n", BCT, x, y,
	  env->map[y][x].resource[FOOD],
	  env->map[y][x].resource[LINEMATE],
	  env->map[y][x].resource[DERAUMERE],
	  env->map[y][x].resource[SIBUR],
	  env->map[y][x].resource[MENDIANE],
	  env->map[y][x].resource[PHIRAS],
	  env->map[y][x].resource[THYSTAME]);
  return (1);
}

int	g_bct(t_env *env, t_client *client, t_list **current)
{
  int	x;
  int	y;

  (void)current;
  x = atoi(client->split_cmd[1]);
  y = atoi(client->split_cmd[2]);
  bct_f(x, y, env, client);
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
	  ++y;
	}
      y = 0;
      ++x;
    }
  return (1);
}

int	g_tna(t_env *env, t_client *client, t_list **current)
{
  int	i;
  char	*str;

  i = 0;
  (void)current;
  (void)client;
  while (i < env->arg.nb_team)
    {
      if ((str = malloc(strlen(env->arg.team[i].team_name) + 6)) == NULL)
	{
	  perror(MALLOC);
	  exit(-1);
	}
      sprintf(str, "%s %s\n", TNA, env->arg.team[i].team_name);
      free(str);
    }
  return (1);
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
  n = atoi(client->split_cmd[1]);
  cli_temp = search_client(current, n, env);
  size = sprintf(buff, "%d%d%d\n", n, cli_temp->pos.x, cli_temp->pos.y);
  size += 5;
  dir = def_dir(cli_temp);
  str = malloc(size+1);
  sprintf(str, "%s %d %d %d %d\n", PPO, n, cli_temp->pos.x, cli_temp->pos.y, dir);
  free(str);
  return (1);
}

int		g_plv(t_env *env, t_client *client, t_list **current)
{
  //  t_list	*tmp;
  t_client	*cli_temp;
  char		*str;
  char		buff[13];
  int		size;
  int		n;

  (void)env;
  n = atoi(client->split_cmd[1]);
  cli_temp = search_client(current, n, env);
  size = sprintf(buff, "%d\n", n);
  if ((str = malloc(size + 7)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d\n", PLV, n, cli_temp->level);
  free(str);
  return (1);
} 


t_client	*search_client(t_list **current, int n, t_env *env)
{
  t_list	*tmp;
  t_client	*client_temp;
  int		i;
  
  tmp = *current;
  while (i < env->nb_player)
    {
      client_temp = tmp->data;
      if (client_temp->socket == n)
	return (client_temp);
      tmp = tmp->next;
      i++;
    }
  return (NULL);
}

int		g_pin(t_env *env, t_client *client, t_list **current)
{
  t_client	*cli_temp;
  char		buff[13];
  char		*str;
  int		size;
  int		n;

  (void)client;
  n = atoi(client->split_cmd[1]);
  cli_temp = search_client(current, n, env);
  size = sprintf(buff, " %d\n", n);
  size += sprintf(buff, " %d", cli_temp->inventory[FOOD]);
  size += sprintf(buff, " %d", cli_temp->inventory[LINEMATE]);
  size += sprintf(buff, " %d", cli_temp->inventory[DERAUMERE]);
  size += sprintf(buff, " %d", cli_temp->inventory[SIBUR]);
  size += sprintf(buff, " %d", cli_temp->inventory[MENDIANE]);
  size += sprintf(buff, " %d", cli_temp->inventory[PHIRAS]);
  size += sprintf(buff, " %d", cli_temp->inventory[THYSTAME]);
  size += sprintf(buff, " %d", cli_temp->pos.x);
  size += sprintf(buff, " %d", cli_temp->pos.y);
  if ((str = malloc(size + 4)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d %d %d %d %d %d %d %d %d\n", PIN, n, cli_temp->pos.x, cli_temp->pos.y,
	  cli_temp->inventory[FOOD],
	  cli_temp->inventory[LINEMATE],
	  cli_temp->inventory[DERAUMERE],
	  cli_temp->inventory[SIBUR],
	  cli_temp->inventory[MENDIANE],
	  cli_temp->inventory[PHIRAS],
	  cli_temp->inventory[THYSTAME]);
  free(str);
  return (1);
}

int	def_dir(t_client *client)
{
  (void)client;
  return (1);
}
