/*
** main.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:23:46 2017 Gregoire Renard
** Last update Tue Jun 20 19:32:41 2017 Gregoire Renard
*/

#include <stdlib.h>
#include "server.h"

static void	free_map(t_env *env)
{
  int		cpt;

  cpt = 0;
  if (env->map != NULL)
    {
      while (env->map[cpt] != NULL)
	{
	  free(env->map[cpt]);
	  cpt++;
	}
      free(env->map);
    }
}

static void	free_env(t_env *env)
{
  int		cpt;

  cpt = 0;
  if (env->arg.name_team != NULL)
    {
      while (env->arg.name_team[cpt] != NULL)
	{
	  free(env->arg.name_team[cpt]);
	  cpt++;
	}
      free(env->arg.name_team);
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
  if (!my_init_server(&env) ||
      my_zappy_server(&env))
    {
      free_env(&env);
      return (ERROR);
    }
  free_env(&env);
  return (SUCCESS);
}
