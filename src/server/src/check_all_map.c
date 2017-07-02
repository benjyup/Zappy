/*
** check_all_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 15:20:24 2017 Gregoire Renard
** Last update Sun Jul  2 22:04:10 2017 Gregoire Renard
*/

#include "server.h"

static void	set_message(char **message, int port)
{
  int		cpt;

  cpt = 0;
  while ((*message)[cpt] != '\0' &&
	 ((*message)[cpt] < '0' || (*message)[cpt] > '9'))
    cpt++;
  (*message)[cpt] = port + 48;
}

static int	know_border(t_client *sender,
			    t_client *receiver)
{
  if (sender->pos.x == receiver->pos.x)
    return (vertical_port(sender, receiver));
  if (sender->pos.y == receiver->pos.y)
    return (horizontal_port(sender, receiver));
  else
    return (border_port(sender, receiver));
}

static void	find_all_clients(t_client *client,
				 char **message,
				 t_client **clients)
{
  int		cpt;
  int		border;

  cpt = 0;
  if (clients[0] != NULL &&
      clients[0] != client)
    {
      while (clients[cpt] != NULL)
	{
	  if (clients[cpt] != client &&
	      (clients[cpt]->pos.y != client->pos.y ||
	       clients[cpt]->pos.x != client->pos.x))
	    {
	      border = know_border(client, clients[cpt]);
	      set_message(message, border);
	      my_send(clients[cpt], *message, 0);
	    }
	  cpt++;
	}
    }
}

void		check_all_map(t_env *env, t_client *client,
			      char **message)
{
  t_pos		pos;

  pos.y = 0;
  while (env->map[pos.y] != NULL)
    {
      pos.x = 0;
      while (env->map[pos.y][pos.x].border != 1)
	{
	  find_all_clients(client, message,
			   env->map[pos.y][pos.x].clients);
	  pos.x++;
	}
      pos.y++;
    }
}
