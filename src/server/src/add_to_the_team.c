/*
** add_to_the_team.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed Jun 21 14:55:57 2017 Gregoire Renard
** Last update Wed Jun 28 18:26:06 2017 Gregoire Renard
*/

#include "server.h"

static void	send_pos(t_env *env, t_client *client,
			 char *tmp)
{
  char		*x;
  char		*y;

  (void)env;
  x = to_string(env->arg.width);
  y = to_string(env->arg.height);
  if ((tmp = realloc(tmp, strlen(tmp) + strlen(x)
		     + strlen(y) + 3)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  strcat(tmp, x);
  strcat(tmp, " ");
  strcat(tmp, y);
  strcat(tmp, "\n\0");
  my_send(client, tmp);
  g_pnw(env, client, &env->clients->next);
  free(tmp);
}

static void	send_info(t_env *env, t_client *client, int cpt)
{
  char		*ret;
  int		len;

  ret = to_string(env->arg.clients_lim - env->arg.team[cpt].nb_player);
  len = strlen(ret);
  if ((ret = realloc(ret, len + 2)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  ret[len] = '\n';
  ret[len + 1] = 0;
  send_pos(env, client, ret);
  free(ret);
}

static void	init_pos_client(t_env *env, t_client *client, int cpt)
{
  t_pos		pos;

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
  client->pos.x = pos.x;
  client->pos.y = pos.y;
  add_in_map(env, client);
  send_info(env, client, cpt);
}

static void	init_variable(t_client *client)
{
  int		cpt;

  cpt = 0;
  while (cpt != MAX_RESOURCE)
    {
      client->inventory[cpt] = 0;
      cpt++;
    }
  client->type = player;
  client->level = 1;
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
	      init_variable(client);
	      init_pos_client(env, client, cpt);
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
