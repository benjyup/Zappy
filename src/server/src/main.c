/*
** main.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:23:46 2017 Gregoire Renard
** Last update Tue Jun 20 17:14:14 2017 Gregoire Renard
*/

#include <stdlib.h>
#include "server.h"

static void	free_arg(t_env *env)
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
    }
  free(env->arg.name_team);
}

int		main(int argc, char **argv)
{
  t_env		env;

  (void)argc;
  if ((init_arg(&env, argv)) == ERROR)
    {
      free_arg(&env);
      return (print_help(ERROR));
    }
  if (!my_init_server(&env) ||
      my_zappy_server(&env))
    return (ERROR);
  free_arg(&env);
  return (SUCCESS);
}
