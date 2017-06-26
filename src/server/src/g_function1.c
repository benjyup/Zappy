#include <stdio.h>
#include "server.h"

int		g_enw(t_client *client, int player,int egg, int x, int y)
{
  char		buff[128];

  sprintf(buff, "enw %d %d %d %d\n", egg, player, x, y);
  my_send(client, buff);
  return (1);
}

int		g_pdi(t_client *client, int player)
{
  char		buff[32];

  sprintf(buff, "pdi %d\n", player);
  my_send(client, buff);
  return (1);
}

int		g_pgt(t_client *client, int player, int ress)
{
  char		buff[64];

  sprintf(buff, "pgt %d %d\n", player, ress);
  my_send(client, buff);
  return (1);
}

int		g_pdr(t_client *client, int player, int ress)
{
  char		buff[64];

  sprintf(buff, "pdr %d %d\n", player, ress);
  my_send(client, buff);
  return (1);
}

int		g_pfk(t_client *client, int player)
{
  char		buff[32];

  sprintf(buff, "pfk %d\n", player);
  my_send(client, buff);
  return (1);
}
