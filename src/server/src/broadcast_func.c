/*
** broadcast_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 23 14:39:30 2017 Gregoire Renard
** Last update Fri Jun 23 16:24:59 2017 Gregoire Renard
*/

#include "server.h"

static void	init_message(char **message, t_client *client)
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
  strcat(*message, "\0");
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
  /* t_pos		pos; */
  char		*message;

  (void)env;
  (void)current;
  decale = 0;
  /* pos.x = client->pos.x; */
  /* pos.y = client->pos.y; */
  init_message(&message, client);
  while (decale <= 8)
    {
      if (decale != 0)
  	set_message(&message, decale);
      decale++;
    }
  free(message);
  return (SUCCESS);
}
