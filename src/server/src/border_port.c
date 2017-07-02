/*
** border_port.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 16:32:45 2017 Gregoire Renard
** Last update Sun Jul  2 22:03:51 2017 Gregoire Renard
*/

#include "server.h"

static int	border_hightl(t_client *receiver)
{
  int		dir;

  if (receiver->dir.x == 1)
    dir = 8;
  else if (receiver->dir.x == -1)
    dir = 4;
  else if (receiver->dir.y == 1)
    dir = 2;
  else if (receiver->dir.y == -1)
    dir = 6;
  return (dir);
}

static int	border_downl(t_client *receiver)
{
  int		dir;

  if (receiver->dir.x == 1)
    dir = 2;
  else if (receiver->dir.x == -1)
    dir = 6;
  else if (receiver->dir.y == 1)
    dir = 4;
  else if (receiver->dir.y == -1)
    dir = 8;
  return (dir);
}

static int	border_hightr(t_client *receiver)
{
  int		dir;

  if (receiver->dir.x == 1)
    dir = 6;
  else if (receiver->dir.x == -1)
    dir = 2;
  else if (receiver->dir.y == 1)
    dir = 8;
  else if (receiver->dir.y == -1)
    dir = 4;
  return (dir);
}

static int	border_downr(t_client *receiver)
{
  int		dir;

  if (receiver->dir.x == 1)
    dir = 4;
  else if (receiver->dir.x == -1)
    dir = 8;
  else if (receiver->dir.y == 1)
    dir = 6;
  else if (receiver->dir.y == -1)
    dir = 2;
  return (dir);
}

int		border_port(t_client *sender,
			    t_client *receiver)
{
  int		dir;

  if (sender->pos.x > receiver->pos.x
      && sender->pos.y > receiver->pos.y)
    dir = border_hightl(receiver);
  if (sender->pos.x > receiver->pos.x
      && sender->pos.y < receiver->pos.y)
    dir = border_downl(receiver);
  if (sender->pos.x < receiver->pos.x
      && sender->pos.y > receiver->pos.y)
    dir = border_hightr(receiver);
  if (sender->pos.x < receiver->pos.x
      && sender->pos.y < receiver->pos.y)
    dir = border_downr(receiver);
  return (dir);
}
