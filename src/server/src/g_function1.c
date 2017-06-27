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
