/*
** init_arg.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 11:45:20 2017 Gregoire Renard
** Last update Fri Jun 30 17:06:37 2017 Gregoire Renard
*/

#include "server.h"

static int		init_pointer(t_pointer *pointer)
{
  if ((pointer[0].opt = strdup("-p")) == NULL)
    return (ERROR);
  pointer[0].func = &opt_p;
  if ((pointer[1].opt = strdup("-x")) == NULL)
    return (ERROR);
  pointer[1].func = &opt_x;
  if ((pointer[2].opt = strdup("-y")) == NULL)
    return (ERROR);
  pointer[2].func = &opt_y;
  if ((pointer[3].opt = strdup("-n")) == NULL)
    return (ERROR);
  pointer[3].func = &opt_n;
  if ((pointer[4].opt = strdup("-c")) == NULL)
    return (ERROR);
  pointer[4].func = &opt_c;
  if ((pointer[5].opt = strdup("-f")) == NULL)
    return (ERROR);
  pointer[5].func = &opt_f;
  return (SUCCESS);
}

static void		set_arg(t_env *env)
{
  env->arg.port = -1;
  env->arg.width = -1;
  env->arg.height = -1;
  env->arg.team = NULL;
  env->arg.clients_lim = -1;
  env->arg.freq = 100;
  env->nb_player = 0;
  env->nb_eggs = 0;
  init_env_resources(env);
}

static void		free_pointer(t_pointer *pointer)
{
  int			cpt;

  cpt = 0;
  while (cpt <= 5)
    {
      free(pointer[cpt].opt);
      cpt++;
    }
}

int			init_arg(t_env *env, char **argv)
{
  t_pointer		pointer[MAX_CMD];
  t_pointer		*tmp;
  int			cpt;

  cpt = 1;
  tmp = pointer;
  if ((init_pointer(tmp)) == ERROR)
    return (ERROR);
  set_arg(env);
  while (argv[cpt] != NULL)
    if ((check_opt(argv, &cpt, env, tmp)) == ERROR)
      {
	free_pointer(tmp);
	return (ERROR);
      }
  free_pointer(tmp);
  if (env->arg.port == -1 || env->arg.width == -1
      || env->arg.height == -1 || env->arg.team == NULL
      || env->arg.clients_lim == -1 || env->arg.freq == -1)
    return (ERROR);
  env->time_one_unit = (1260 / env->arg.freq) / 10;
  env->real_start = 0;
  return (SUCCESS);
}
