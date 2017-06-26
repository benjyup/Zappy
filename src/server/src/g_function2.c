#include <stdio.h>
#include "server.h"

int		g_smg(t_client *client, char *str)
{
  char		*buff;

  if ((buff = malloc(strlen(str) + 6)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(buff, "smg %s\n", str);
  my_send(client, buff);
  free(buff);
  return (1);
}

int		g_seg(t_client *client, char *str)
{
  char		*buff;

  if ((buff = malloc(strlen(str) + 6)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(buff, "smg %s\n", str);
  my_send(client, buff);
  free(buff);
  return (1);
}

int		g_edi(t_client *client, int egg)
{
  char		buff[32];

  sprintf(buff, "edi %d\n", egg);
  my_send(client, buff);
  return (1);
}

int		g_ebo(t_client *client, int egg)
{
  char		buff[32];

  sprintf(buff, "ebo %d\n", egg);
  my_send(client, buff);
  return (1);
}

int		g_eht(t_client *client, int egg)
{
  char		buff[32];

  sprintf(buff, "eht %d\n", egg);
  my_send(client, buff);
  return (1);
}
