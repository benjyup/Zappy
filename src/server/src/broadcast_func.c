/*
** broadcast_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 23 14:39:30 2017 Gregoire Renard
** Last update Sun Jul  2 17:33:14 2017 Gregoire Renard
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

int		broadcast_func(t_env *env, t_client *client,
			       t_list **current)
{
  t_pos		pos;
  char		*message;

  (void)current;
  if (client->split_cmd[1] != NULL)
    {
      init_message(&message, client, &pos);
      g_pbc(client, env, client->split_cmd[1]);
      send_to_all_user(env, pos, client, message);
      check_all_map(env, client, &message);
      free(message);
      my_send(client, OK, 7 / env->arg.freq);
    }
  else
    my_send(client, KO, 7 / env->arg.freq);
  return (SUCCESS);
}
