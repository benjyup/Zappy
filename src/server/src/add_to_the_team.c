/*
** add_to_the_team.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed Jun 21 14:55:57 2017 Gregoire Renard
** Last update Sun Jul  2 10:18:46 2017 Gregoire Renard
*/

#include "server.h"

static void	send_pos(t_env *env, t_client *client)
{
  char		*x;
  char		*y;
  char		*tmp;

  (void)env;
  x = to_string(env->arg.width);
  y = to_string(env->arg.height);
  if ((tmp = malloc(strlen(x) + strlen(y) + 3)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  strcpy(tmp, x);
  strcat(tmp, " ");
  strcat(tmp, y);
  strcat(tmp, "\n\0");
  my_send(client, tmp, 0);
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
  my_send(client, ret, 0);
  send_pos(env, client);
  free(ret);
}

static void	init_pos_client(t_env *env, t_client *client, int cpt,
				t_pos new_pos)
{
  client->pos.x = new_pos.x;
  client->pos.y = new_pos.y;
  if (new_pos.x == -1 && new_pos.y == -1)
    {
      client->pos.x = rand() % env->arg.width;
      client->pos.y = rand() % env->arg.height;
      while (env->map[client->pos.y][client->pos.x].name_team != NULL ||
	     (env->map[client->pos.y][client->pos.x].name_team != NULL &&
	      (strcmp(env->map[client->pos.y][client->pos.x].name_team,
		      client->name_team)) != 0))
	{
	  client->pos.x = rand() % env->arg.width;
	  client->pos.y = rand() % env->arg.height;
	}
    }
  if (env->map[client->pos.y][client->pos.x].name_team == NULL)
    env->map[client->pos.y][client->pos.x].name_team = client->name_team;
  add_in_map(env, client);
  send_info(env, client, cpt);
}

static void	init_variable(t_client *client, t_env *env)
{
  int		cpt;

  cpt = 1;
  client->inventory[0] = 10;
  while (cpt != MAX_RESOURCE)
    {
      client->inventory[cpt] = 0;
      cpt++;
    }
  client->type = player;
  client->level = 1;
  client->time_unit = time(NULL);
  client->rst_time_unit = env->time_one_unit;
}

int		add_to_the_team(t_env *env, t_client *client,
				t_pos new_pos)
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
	      init_variable(client, env);
	      init_pos_client(env, client, cpt, new_pos);
	      return (SUCCESS);
	    }
	  else
	    {
	      my_send(client, KO, 0);
	      return (ERROR);
	    }
	}
      cpt++;
    }
  my_send(client, KO, 0);
  return (ERROR);
}
