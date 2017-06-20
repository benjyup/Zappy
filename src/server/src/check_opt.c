/*
** check_opt.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 14:19:46 2017 Gregoire Renard
** Last update Tue Jun 20 14:47:29 2017 Gregoire Renard
*/

#include "server.h"

int		check_opt(char **argv,
			  int *cpt,
			  t_env *env,
			  t_pointer *pointer)
{
  int		cpt_arg;

  cpt_arg = 0;
  while (cpt_arg != MAX_CMD)
    {
      if ((strcmp(pointer[cpt_arg].opt, argv[*cpt])) == 0)
	{
	  if ((pointer[cpt_arg].func(env, argv, cpt)) == ERROR)
	    return (ERROR);
	  return (SUCCESS);
	}
      cpt_arg++;
    }
  return (ERROR);
}
