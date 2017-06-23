/*
** add_to_the_team.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed Jun 21 14:55:57 2017 Gregoire Renard
** Last update Fri Jun 23 13:06:55 2017 Gregoire Renard
*/

#include "server.h"

static void	send_pos(t_env *env, t_client *client)
{
  char		*x;
  char		*y;
  char		*tmp;

  (void)env;
  x = to_string(client->pos.x);
  y = to_string(client->pos.y);
  if ((tmp = malloc(strlen(x) + strlen(y) + 3)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  strcpy(tmp, x);
  strcat(tmp, " ");
  strcat(tmp, y);
  strcat(tmp, "\n\0");
  my_send(client, tmp);
  free(tmp);
}

static void	send_info(t_env *env, t_client *client)
{
  char		*ret;
  int		len;

  ret = to_string(env->arg.clients_lim);
  len = strlen(ret);
  if ((ret = realloc(ret, len + 2)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  ret[len] = '\n';
  ret[len + 1] = 0;
  my_send(client, ret);
  send_pos(env, client);
  free(ret);
}

static void	init_pos_client(t_env *env, t_client *client)
{
  t_pos		pos;
  int		cpt;

  cpt = 0;
  pos.x = rand() % env->arg.width;
  pos.y = rand() % env->arg.height;
  while (env->map[pos.y][pos.x].name_team != NULL ||
      	 (env->map[pos.y][pos.x].name_team != NULL &&
	  (strcmp(env->map[pos.y][pos.x].name_team,
		  client->name_team)) != 0))
    {
      pos.x = rand() % env->arg.width;
      pos.y = rand() % env->arg.height;
    }
  if (env->map[pos.y][pos.x].name_team == NULL)
    env->map[pos.y][pos.x].name_team = client->name_team;
  while (env->map[pos.y][pos.x].fd_player[cpt] != -1)
    cpt++;
  env->map[pos.y][pos.x].fd_player[cpt] = client->socket;
  client->pos.x = pos.x;
  client->pos.y = pos.y;
  send_info(env, client);
}

static void	init_inventory(t_client *client)
{
  int		cpt;

  cpt = 0;
  while (cpt != MAX_RESOURCE)
    {
      client->inventory[cpt] = 0;
      cpt++;
    }
}

void		add_to_the_team(t_env *env, t_client *client)
{
  int		cpt;

  cpt = 0;
  while (cpt != env->arg.nb_team && cpt != -1)
    {
      if ((strcmp(client->cmd, env->arg.team[cpt].team_name)) == 0)
	{
	  if (env->arg.team[cpt].nb_player < env->arg.clients_lim)
	    {
	      env->arg.team[cpt].nb_player++;
	      client->name_team = env->arg.team[cpt].team_name;
	      init_pos_client(env, client);
	      init_inventory(client);
	    }
	  else
	    {
	      my_send(client, KO);
	      cpt = -2;
	    }
	}
      cpt++;
    }
  if (client->name_team == NULL && cpt != -1)
    my_send(client, KO);
}
