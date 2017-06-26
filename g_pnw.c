#include <stdio.h>
#include "server.h"

int             g_pnw(t_env *env, t_client *client, t_list **current)
{
  char          *str;
  char          buff[13];
  int           size; 
  int           n;

  size = sprintf(buff, " %d", client->socket);
  size += sprintf(buff, " %d", client->pos.x);
  size += sprintf(buff, " %d", client->pos.y);
  size += 11;
  size += strlen(client->name_team);
  if ((str = malloc(size + 1)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(str, "%s %d %d %d %d %s\n", "pnw ", client->socket,
	  client->pos.x,
	  client->pos.y,
	  def_orientaton(client), client->name_team);
  send_graphical(current, env, str);
  free(str);
  return (1);
}
