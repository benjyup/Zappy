/*
** broadcast_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 23 14:39:30 2017 Gregoire Renard
** Last update Wed Jun 28 23:04:15 2017 Gregoire Renard
*/

#include "server.h"

static void	init_message(char **message, t_client *client,
			     t_pos *pos)
{
  if ((*message = strdup("message ")) == NULL
      ||!(*message = realloc(*message, strlen(*message)
			     + 5 + strlen(client->split_cmd[1]))))
    {
      perror(MALLOC);
      exit(ERROR);
    }
  strcat(*message, "0, ");
  strcat(*message, client->split_cmd[1]);
  strcat(*message, "\n\0");
  pos->x = client->pos.x;
  pos->y = client->pos.y;
}

static void	set_message(char **message, int decale)
{
  int		cpt;

  cpt = 0;
  while ((*message)[cpt] != decale + 48 - 1)
    cpt++;
  (*message)[cpt] = decale + 48;
}

int		broadcast_func(t_env *env, t_client *client,
			       t_list **current)
{
  int		decale;
  t_pos		pos;
  char		*message;

  (void)current;
  if (client->split_cmd[1] != NULL)
    {
      decale = 0;
      init_message(&message, client, &pos);
      g_pbc(client, env, client->split_cmd[1]);
      send_to_all_user(env, pos, client, message);
      while (decale < 8)
	{
	  decale++;
	  set_message(&message, decale);
	  set_broadcast_pos(env, client, &pos, message);
	}
      free(message);
      my_send(client, OK, 7 / env->arg.freq);
    }
  else
    my_send(client, KO, 7 / env->arg.freq);
  return (SUCCESS);
}
