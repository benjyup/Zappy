/*
** inventory_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 17:22:44 2017 Gregoire Renard
** Last update Wed Jun 28 23:03:22 2017 Gregoire Renard
*/

#include "server.h"

static void	init_tmp(char **tmp)
{
  if ((*tmp = malloc(3)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  (*tmp)[0] = '[';
  (*tmp)[1] = ' ';
  (*tmp)[2] = '\0';
}

static int	remp_tmp(t_env *env, t_client *client,
			 int cpt, char **tmp)
{
  int		len_tmp;
  char		*nb;

  len_tmp = strlen(*tmp);
  nb = to_string(client->inventory[cpt]);
  if ((*tmp = realloc(*tmp, len_tmp
		      + strlen(env->resources[cpt])
		      + strlen(nb) + 5)) == NULL)
    return (ERROR);
  strcat(*tmp, env->resources[cpt]);
  strcat(*tmp, " ");
  strcat(*tmp, nb);
  if (cpt + 1 == MAX_RESOURCE)
    strcat(*tmp, " ]\n");
  else
    strcat(*tmp, ", ");
  strcat(*tmp, "\0");
  return (SUCCESS);
}

int		inventory_func(t_env *env, t_client *client,
			       t_list **current)
{
  int		cpt;
  char		*tmp;

  (void)current;
  cpt = 0;
  init_tmp(&tmp);
  while (cpt != MAX_RESOURCE)
    {
      if ((remp_tmp(env, client, cpt, &tmp)) == ERROR)
	{
	  perror(MALLOC);
	  exit(ERROR);
	}
      cpt++;
    }
  my_send(client, tmp, 1 / env->arg.freq);
  free(tmp);
  return (SUCCESS);
}
