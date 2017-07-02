/*
** vertical_port.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 16:30:06 2017 Gregoire Renard
** Last update Sun Jul  2 17:02:49 2017 Gregoire Renard
*/

#include "server.h"

int		vertical_port(t_client *sender,
			      t_client *receiver)
{
  int		dir;

  if (sender->pos.y > receiver->pos.y)
    {
      if (receiver->dir.x == 1)
	dir = 7;
      else if (receiver->dir.x == -1)
	dir = 3;
      else if (receiver->dir.y == 1)
	dir = 1;
      else if (receiver->dir.y == -1)
	dir = 5;
    }
  else
    if (receiver->dir.x == 1)
      dir = 3;
    else if (receiver->dir.x == -1)
      dir = 7;
    else if (receiver->dir.y == 1)
      dir = 5;
    else if (receiver->dir.y == -1)
      dir = 1;
  return (dir);
}
