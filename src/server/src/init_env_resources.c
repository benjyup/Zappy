/*
** init_tab_resources.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 17:32:11 2017 Gregoire Renard
** Last update Fri Jun 23 12:50:51 2017 Gregoire Renard
*/

#include "server.h"

static int	init_str(t_env *env)
{
  if ((env->resources[0] = strdup("food")) == NULL
      || (env->resources[1] = strdup("linemate")) == NULL
      || (env->resources[2] = strdup("deraumere")) == NULL
      || (env->resources[3] = strdup("sibur")) == NULL
      || (env->resources[4] = strdup("mendiane")) == NULL
      || (env->resources[5] = strdup("phiras")) == NULL
      || (env->resources[6] = strdup("thystame")) == NULL)
    return (ERROR);
  return (SUCCESS);
}

void		init_env_resources(t_env *env)
{
  if ((env->resources = malloc(sizeof(char *)
			       * (MAX_RESOURCE + 1))) == NULL
      || (init_str(env)) == ERROR)
    {
      perror(MALLOC);
      exit(ERROR);
    }
}
