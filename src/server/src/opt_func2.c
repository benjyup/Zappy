/*
** opt_func2.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 14:31:23 2017 Gregoire Renard
** Last update Tue Jun 20 18:35:39 2017 Gregoire Renard
*/

#include "server.h"

int		count_len(char **argv, int cpt)
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

int		opt_n(t_env *env,
		      char **argv,
		      int *cpt)
{
  int		len;
  int		cpt_name;
  
  *cpt = *cpt + 1;
  cpt_name = 0;
  len = count_len(argv, *cpt);
  if ((env->arg.name_team = malloc(sizeof(char *) * (len + 1))) == NULL)
    return (ERROR);
  while (cpt_name != len)
    {
      if ((env->arg.name_team[cpt_name] = strdup(argv[*cpt])) == NULL)
	return (ERROR);
      cpt_name++;
      *cpt = *cpt + 1;
    }
  env->arg.name_team[cpt_name] = NULL;
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
  if (env->arg.clients_lim <= 0)
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
