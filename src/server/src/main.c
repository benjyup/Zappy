/*
** main.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:23:46 2017 Gregoire Renard
** Last update Sun Jul  2 17:12:05 2017 Gregoire Renard
*/

#include <stdlib.h>
#include "server.h"

static void	free_map(t_env *env)
{
  t_pos		pos;

  if (env->map != NULL)
    {
      pos.y = 0;
      while (env->map[pos.y] != NULL)
	{
	  pos.x = 0;
	  while (env->map[pos.y][pos.x].border != 1)
	    {
	      free(env->map[pos.y][pos.x].clients);
	      pos.x++;
	    }
	  free(env->map[pos.y]);
	  pos.y++;
	}
      free(env->map);
    }
}

static void	free_env(t_env *env)
{
  int		cpt;

  cpt = 0;
  if (env->arg.team != NULL)
    {
      while (cpt != env->arg.nb_team)
	{
	  free(env->arg.team[cpt].team_name);
	  cpt++;
	}
      free(env->arg.team);
      cpt = 0;
      while (env->resources[cpt] != NULL)
	{
	  free(env->resources[cpt]);
	  cpt++;
	}
      free(env->resources);
    }
  free_map(env);
}

int		main(int argc, char **argv)
{
  t_env		env;

  (void)argc;
  env.map = NULL;
  if ((init_arg(&env, argv)) == ERROR ||
      (init_map(&env)) == ERROR)
    {
      free_env(&env);
      return (print_help(ERROR));
    }
  init_elevation(&env);
  if (!init_server(&env) ||
      my_zappy_server(&env))
    {
      free_env(&env);
      return (ERROR);
    }
  free_env(&env);
  return (SUCCESS);
}
