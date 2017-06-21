/*
** add_to_the_team.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed Jun 21 14:55:57 2017 Gregoire Renard
** Last update Wed Jun 21 16:44:12 2017 Gregoire Renard
*/

#include "server.h"

static void	init_pos_client(t_env *env, t_client *client)
{
  t_pos		pos;

  pos.x = rand() % env->arg.width;
  pos.y = rand() % env->arg.height;
  while (env->map[pos.y][pos.x].name_team == NULL ||
      	 (env->map[pos.y][pos.x].name_team != NULL &&
	  (strcmp(env->map[pos.y][pos.x].name_team,
		  client->name_team)) == 0))
    {
      pos.x = rand() % env->arg.width;
      pos.y = rand() % env->arg.height;
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
	    }
	  else
	    {
	      my_send(client->socket, KO);
	      cpt = -2;
	    }
	}
      cpt++;
    }
  if (client->name_team == NULL && cpt != -1)
    my_send(client->socket, KO);
}
