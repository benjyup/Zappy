/*
** set_pos_start.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 27 17:32:16 2017 Gregoire Renard
** Last update Tue Jun 27 18:27:02 2017 Gregoire Renard
*/

#include "server.h"

static void	init_target_tmp(t_client *client, t_look *look)
{
  look->tmp.x = client->pos.x + client->dir.x * look->cpt;
  look->tmp.y = client->pos.y + client->dir.y * look->cpt;
  look->target.x = client->pos.x + client->dir.x * look->cpt;
  look->target.y = client->pos.y + client->dir.y * look->cpt;
}

static void	set_target_tmp(t_client *client, t_look *look)
{
  if (client->dir.x == 1)
    {
      look->tmp.y -= look->cpt;
      look->target.y += look->cpt + 1;
    }
  else if (client->dir.x == -1)
    {
      look->tmp.y += look->cpt;
      look->target.y -= look->cpt + 1;
    }
  else if (client->dir.y == 1)
    {
      look->tmp.x += look->cpt;
      look->target.x -= look->cpt + 1;
    }
  else if (client->dir.y == -1)
    {
      look->tmp.x -= look->cpt;
      look->target.x += look->cpt + 1;
    }
}

static void	adjust_target_tmp(t_look *look,
				  t_env *env)
{
  if (look->tmp.x < 0)
    look->tmp.x = env->arg.width + look->tmp.x;
  else
    look->tmp.x = look->tmp.x % env->arg.width;
  if (look->tmp.y < 0)
    look->tmp.y = env->arg.height + look->tmp.y;
  else
    look->tmp.y = look->tmp.y % env->arg.height;
  if (look->target.x < 0)
    look->target.x = env->arg.width + look->target.x;
  else
    look->target.x = look->target.x % env->arg.width;
  if (look->target.y < 0)
    look->target.y = env->arg.height + look->target.y;
  else
    look->target.y = look->target.y % env->arg.height;
}

void		set_pos_start(t_env *env, t_client *client,
			      t_look *look)
{
  init_target_tmp(client, look);
  set_target_tmp(client, look);
  adjust_target_tmp(look, env);
}
