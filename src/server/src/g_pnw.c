/*
** g_pnw.c for zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:21:28 2017 rodrigue rene
** Last update Tue Jun 27 19:28:58 2017 Gregoire Renard
*/

#include <stdio.h>
#include "server.h"

int             g_pnw(t_env *env, t_client *client, t_list **current)
{
  char          *str;
  char          buff[13];
  int           size;

  size = sprintf(buff, " %d", client->socket);
  size += sprintf(buff, " %d", client->pos.x);
  size += sprintf(buff, " %d", client->pos.y);
  size += sprintf(buff, " %d", client->level);
  size += 11;
  size += strlen(client->name_team);
  if ((str = malloc(size + 1)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d %d %d %d %s\n", "pnw ", client->socket,
	  client->pos.x,
	  client->pos.y,
	  def_dir(client), client->level, client->name_team);
  send_graphical(current, env, str, 0);
  free(str);
  return (1);
}

int             g_pdr(t_env *env, t_client *client, t_list **current, int ress)
{
  char          *str;
  char          buff[13];
  int           size;

  size = sprintf(buff, " %d", client->socket);
  size += 7;
  if ((str = malloc(size)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d\n", "pdr ", client->socket, ress);
  send_graphical(current, env, str, 0);
  free(str);
  return (1);
}

int             g_pgt(t_env *env, t_client *client, t_list **current, int ress)
{
  char          *str;
  char          buff[13];
  int           size;

  size = sprintf(buff, " %d", client->socket);
  size += 7;
  if ((str = malloc(size)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d\n", "pgt ", client->socket, ress);
  send_graphical(current, env, str, 0);
  free(str);
  return (1);
}
