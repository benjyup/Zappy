/*
** know_team.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 13:06:07 2017 Gregoire Renard
** Last update Fri Jun 30 18:23:25 2017 Gregoire Renard
*/

#include "server.h"

static void	change_egg(int i, t_env *env, t_pos *pos_egg)
{
  t_eggs	*eggs;

  eggs = (t_eggs *)(env->arg.team[i].eggs->next->data);
  if (env->arg.team[i].eggs->next->data != NULL)
    {
      pos_egg->x = eggs->pos.x;
      pos_egg->y = eggs->pos.y;
      g_ebo(env, eggs->id);
      my_del_elem(env->arg.team[i].eggs, env->arg.team[i].eggs->next, NULL);
    }
}

static void	find_egg(t_pos *pos_egg, char *str, t_env *env)
{
  int		i;

  i = 0;
  pos_egg->x = -1;
  pos_egg->y = -1;
  while (i < env->arg.nb_team)
    {
      if (!strcmp(str, env->arg.team[i].team_name))
	{
	  change_egg(i, env, pos_egg);
	  i = env->arg.nb_team;
	}
      i++;
    }
}

static void     connection_gr(t_env *env, t_client *client)
{
  g_msz(env, client, &env->clients->next);
  g_sgt(env, client, &env->clients->next);
  g_mct(env, client, &env->clients->next);
  g_tna(env, client, &env->clients->next);
}

void		know_team(t_env *env, t_client *client)
{
  t_pos		pos_egg;

  if ((strcmp("GRAPHIC", client->cmd)) == 0)
    {
      client->type = monitor;
      client->name_team = "GRAPHIC";
      connection_gr(env, client);
    }
  else
    {
      find_egg(&pos_egg, client->cmd, env);
      if ((add_to_the_team(env, client, pos_egg)) != ERROR)
	g_pnw(env, client, &env->clients->next);
    }
}
