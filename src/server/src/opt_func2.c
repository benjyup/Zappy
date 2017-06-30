/*
** opt_func2.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 14:31:23 2017 Gregoire Renard
** Last update Fri Jun 30 17:04:46 2017 Gregoire Renard
*/

#include "server.h"

static int	count_len(char **argv, int cpt)
{
  int		save;

  save = cpt;
  while (argv[cpt] != NULL)
    {
      if (argv[cpt][0] == '-')
	return (cpt - save);
      cpt++;
    }
  return (cpt - save);
}

static int	check_double(t_env *env)
{
  int		cpt;
  int		cpt2;

  cpt = 0;
  while (cpt != env->arg.nb_team)
    {
      if ((strcmp("GRAPHIC", env->arg.team[cpt].team_name)) == 0)
	return (ERROR);
      cpt++;
    }
  cpt = 0;
  while (cpt != env->arg.nb_team)
    {
      cpt2 = cpt + 1;
      while (cpt2 != env->arg.nb_team)
	{
	  if ((strcmp(env->arg.team[cpt].team_name,
		      env->arg.team[cpt2].team_name)) == 0)
	    return (ERROR);
	  cpt2++;
	}
      cpt++;
    }
  return (SUCCESS);
}

int		opt_n(t_env *env,
		      char **argv,
		      int *cpt)
{
  int		len;
  int		cpt_name;

  *cpt = *cpt + 1;
  cpt_name = 0;
  len = count_len(argv, *cpt);
  env->arg.nb_team = len;
  if (len <= 1 ||
      (env->arg.team = malloc(sizeof(t_team) * (len + 1))) == NULL)
    return (ERROR);
  while (cpt_name != len)
    {
      if ((env->arg.team[cpt_name].team_name = strdup(argv[*cpt])) == NULL)
	return (ERROR);
      env->arg.team[cpt_name].eggs = my_init_list();
      env->arg.team[cpt_name].nb_player = 0;
      cpt_name++;
      *cpt = *cpt + 1;
    }
  if ((check_double(env)) == ERROR)
    return (printf_error("Error : team name invalid"));
  return (SUCCESS);
}

int		opt_c(t_env *env,
		      char **argv,
		      int *cpt)
{
  if (argv[(*cpt) + 1] == NULL)
    return (ERROR);
  if ((check_alpha(argv[(*cpt) + 1])) == ERROR)
    return (ERROR);
  env->arg.clients_lim = atoi(argv[(*cpt) + 1]);
  if (env->arg.clients_lim <= 1)
    return (ERROR);
  *cpt = *cpt + 2;
  return (SUCCESS);
}

int		opt_f(t_env *env,
		      char **argv,
		      int *cpt)
{
  if (argv[(*cpt) + 1] == NULL)
    return (ERROR);
  if ((check_alpha(argv[(*cpt) + 1])) == ERROR)
    return (ERROR);
  env->arg.freq = atoi(argv[(*cpt) + 1]);
  if (env->arg.freq <= 0)
    return (ERROR);
  *cpt = *cpt + 2;
  return (SUCCESS);
}
