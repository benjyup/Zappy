/*
** g_function1.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:16:12 2017 rodrigue rene
** Last update Tue Jun 27 17:16:15 2017 rodrigue rene
*/

#include <stdio.h>
#include "server.h"

int		g_enw(t_client *client, int egg, int x, int y)
{
  char		buff[128];

  sprintf(buff, "enw %d %d %d %d\n", egg, client->socket, x, y);
  my_send(client, buff);
  return (1);
}

int		g_pdi(t_client *client)
{
  char		buff[32];

  sprintf(buff, "pdi %d\n", client->socket);
  my_send(client, buff);
  return (1);
}

int		g_pfk(t_client *client)
{
  char		buff[32];

  sprintf(buff, "pfk %d\n", client->socket);
  my_send(client, buff);
  return (1);
}
