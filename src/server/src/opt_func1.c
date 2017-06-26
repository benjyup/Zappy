/*
** opt_func1.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 14:29:13 2017 Gregoire Renard
** Last update Fri Jun 23 16:09:56 2017 Gregoire Renard
*/

#include "server.h"

int		opt_p(t_env *env,
		      char **argv,
		      int *cpt)
{
  if (argv[(*cpt) + 1] == NULL)
    return (ERROR);
  if ((check_alpha(argv[(*cpt) + 1])) == ERROR)
    return (ERROR);
  env->arg.port = atoi(argv[(*cpt) + 1]);
  if (env->arg.port <= 0)
    return (ERROR);
  *cpt = *cpt + 2;
  return (SUCCESS);
}

int		opt_x(t_env *env,
		      char **argv,
		      int *cpt)
{
  if (argv[(*cpt) + 1] == NULL)
    return (ERROR);
  if ((check_alpha(argv[(*cpt) + 1])) == ERROR)
    return (ERROR);
  env->arg.width = atoi(argv[(*cpt) + 1]);
  if (env->arg.width <= 14)
    {
      printf("x and y must be greater than 14\n");
      return (ERROR);
    }
  *cpt = *cpt + 2;
  return (SUCCESS);
}

int		opt_y(t_env *env,
		      char **argv,
		      int *cpt)
{
  if (argv[(*cpt) + 1] == NULL)
    return (ERROR);
  if ((check_alpha(argv[(*cpt) + 1])) == ERROR)
    return (ERROR);
  env->arg.height = atoi(argv[(*cpt) + 1]);
  if (env->arg.height <= 14)
    {
      printf("x and y must be greater than 14\n");
      return (ERROR);
    }
  *cpt = *cpt + 2;
  return (SUCCESS);
}
