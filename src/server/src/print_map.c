/*
** print_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 19:11:36 2017 Gregoire Renard
** Last update Fri Jun 30 13:56:12 2017 Gregoire Renard
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
  while (env->map[pos.y][pos.x].clients[cpt] != NULL)
    cpt++;
  printf("clients = %i, ", cpt);
}

static void		choose_print(t_env *env, t_pos pos)
{
  if (env->map[pos.y][pos.x + 1].border == 1)
    {
      if (env->map[pos.y][pos.x].name_team != NULL)
	printf("%i", env->map[pos.y][pos.x].clients[0]->socket);
      else
	printf("-");
    }
  else
    {
      if (env->map[pos.y][pos.x].name_team != NULL)
	printf("%i, ", env->map[pos.y][pos.x].clients[0]->socket);
      else
	printf("-, ");
    }
}

static void		print_simple_map(t_env *env)
{
  t_pos			pos;

  pos.y = 0;
  while (env->map[pos.y] != NULL)
    {
      pos.x = 0;
      printf("[%i] =\t{", pos.y);
      while (env->map[pos.y][pos.x].border != 1)
	{
	  choose_print(env, pos);
	  pos.x++;
	}
      printf(" }\n");
      pos.y++;
    }
  printf("\n");
}

void			print_map(t_env *env)
{
  t_pos			pos;

  pos.y = 0;
  while (env->map[pos.y] != NULL)
    {
      pos.x = 0;
      printf("----->MAP[%i] ==\n", pos.y);
      while (env->map[pos.y][pos.x].border != 1)
  	{
  	  printf("--->X = %i{%s, ", pos.x, env->map[pos.y][pos.x].name_team);
  	  print_fd(env, pos);
  	  print_resource(env, pos);
  	  pos.x++;
  	  printf("\n");
  	}
      printf("\n");
      pos.y++;
    }
  printf("\n");
  print_simple_map(env);
}
