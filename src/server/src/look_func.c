/*
** look_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 23 13:26:16 2017 Gregoire Renard
** Last update Wed Jun 28 23:17:48 2017 Gregoire Renard
*/

#include "server.h"

static void	init_variable(t_env *env,
			      t_client *client,
			      t_look *look)
{
  look->cpt = 1;
  look->range = client->level;
  if (look->range > 3)
    look->range = 3;
  if ((look->message = strdup("[")) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  look->tmp.x = client->pos.x;
  look->tmp.y = client->pos.y;
  if ((write_component(look, env)) == ERROR)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  look->tmp.x += client->dir.x;
  look->tmp.y += client->dir.y;
}

static void	end_look(t_client *client, t_look *look,
			 t_env *env)
{
  look->message[strlen(look->message) - 1] = 0;
  if ((look->message = realloc(look->message,
			       strlen(look->message) + 3)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  strcat(look->message, "]\n\0");
  my_send(client, look->message, 7 / env->arg.freq);
  free(look->message);
}

static void	adjust_pos(t_look *look, t_client *client,
			   t_env *env)
{
  if (client->dir.x == 1)
    look->tmp.y++;
  else if (client->dir.x == -1)
    look->tmp.y--;
  else if (client->dir.y == 1)
    look->tmp.x--;
  else if (client->dir.y == -1)
    look->tmp.x++;
  if (look->tmp.x < 0)
    look->tmp.x = env->arg.width + look->tmp.x;
  else
    look->tmp.x = look->tmp.x % env->arg.width;
  if (look->tmp.y < 0)
    look->tmp.y = env->arg.height + look->tmp.y;
  else
    look->tmp.y = look->tmp.y % env->arg.height;
}

int		look_func(t_env *env, t_client *client,
			  t_list **current)
{
  t_look	look;

  (void)current;
  init_variable(env, client, &look);
  while (look.cpt <= look.range)
    {
      set_pos_start(env, client, &look);
      while (look.tmp.x != look.target.x || look.tmp.y != look.target.y)
  	{
	  write_component(&look, env);
	  adjust_pos(&look, client, env);
  	}
      look.cpt++;
    }
  end_look(client, &look, env);
  return (SUCCESS);
}
