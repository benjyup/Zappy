/*
** print_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 19:11:36 2017 Gregoire Renard
** Last update Thu Jun 22 17:41:54 2017 Gregoire Renard
*/

#include "server.h"

static void		print_resource(t_env *env, t_pos pos)
{
  printf("food = %i ", env->map[pos.y][pos.x].resource[0]);
  printf("linemate = %i, ", env->map[pos.y][pos.x].resource[1]);
  printf("deraumere = %i, ", env->map[pos.y][pos.x].resource[2]);
  printf("sibur = %i, ", env->map[pos.y][pos.x].resource[3]);
  printf("mendiane = %i, ", env->map[pos.y][pos.x].resource[4]);
  printf("phiras = %i, ", env->map[pos.y][pos.x].resource[5]);
  printf("thystame = %i} ; ", env->map[pos.y][pos.x].resource[6]);
}

static void		print_fd(t_env *env, t_pos pos)
{
  int			cpt;

  cpt = 0;
  while (cpt != env->arg.clients_lim)
    {
      printf("%i, ", env->map[pos.y][pos.x].fd_player[cpt]);
      cpt++;
    }
}

void			print_map(t_env *env)
{
  t_pos			pos;

  pos.y = 0;
  while (env->map[pos.y] != NULL)
    {
      pos.x = 0;
      while (env->map[pos.y][pos.x].border != 1)
	{
	  printf("{%s, ", env->map[pos.y][pos.x].name_team);
	  print_fd(env, pos);
	  print_resource(env, pos);
	  pos.x++;
	}
      printf("\n");
      pos.y++;
    }
  printf("\n");
}
