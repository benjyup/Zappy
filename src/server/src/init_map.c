/*
** init_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 18:25:45 2017 Gregoire Renard
** Last update Sun Jul  2 18:55:18 2017 Gregoire Renard
*/

#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "server.h"

static void	init_resource(t_env *env, t_pos pos)
{
  int		cpt;
  int		nb;

  cpt = 0;
  while (cpt != MAX_RESOURCE)
    {
      nb = rand() % 2;
      if (cpt == FOOD)
	nb += rand() % 50;
      env->map[pos.y][pos.x].resource[cpt] = nb;
      cpt++;
    }
}

static int	init_fd(t_env *env, t_pos pos)
{
  if ((env->map[pos.y][pos.x].clients =
       malloc(sizeof(t_client *) * env->arg.clients_lim + 2)) == NULL)
    {
      printf_error("Error : allocation in init_fd");
      exit(ERROR);
    }
  env->map[pos.y][pos.x].clients[0] = NULL;
  return (SUCCESS);
}

static void	gen_resource(t_env *env)
{
  t_pos		pos;

  pos.y = 0;
  srand(getpid() * time(NULL));
  while (env->map[pos.y] != NULL)
    {
      pos.x = 0;
      while (env->map[pos.y][pos.x].border != 1)
	{
	  env->map[pos.y][pos.x].name_team = NULL;
	  init_fd(env, pos);
	  init_resource(env, pos);
	  pos.x++;
	}
      pos.y++;
    }
}

int		init_map(t_env *env)
{
  t_pos		pos;

  pos.y = 0;
  if ((env->map = malloc(sizeof(t_map *)
			 * (env->arg.height + 1))) == NULL)
    return (ERROR);
  while (pos.y != env->arg.height)
    {
      pos.x = 0;
      if ((env->map[pos.y] = malloc(sizeof(t_map)
				    * (env->arg.width + 1))) == NULL)
	return (ERROR);
      while (pos.x != env->arg.width)
	{
	  env->map[pos.y][pos.x].border = 0;
	  pos.x++;
	}
      env->map[pos.y][env->arg.width].border = 1;
      pos.y++;
    }
  env->map[pos.y] = NULL;
  gen_resource(env);
  return (SUCCESS);
}
