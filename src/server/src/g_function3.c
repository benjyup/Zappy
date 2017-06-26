#include <stdio.h>
#include "server.h"

int		def_dir(t_client *client)
{
  if (client->dir.x == 1)
    return (2);
  if (client->dir.x == 0)
    return (4);
  if (client->dir.y == 0)
    return (1);
  if (client->dir.y == 1)
    return (3);
  return (1);
}

int		g_sbp(t_client *client)
{
  char		buff[5];

  sprintf(buff, "sbp\n");
  my_send(client, buff);
  return (1);
}

int		g_suc(t_client *client)
{
  char		buff[5];

  sprintf(buff, "suc\n");
  my_send(client, buff);
  return (1);
}

int	get_size(t_client *cli_temp, int n)
{
  char	buff[13];
  int	size;
  
  size = sprintf(buff, " %d\n", n);
  size += sprintf(buff, " %d", cli_temp->inventory[FOOD]);
  size += sprintf(buff, " %d", cli_temp->inventory[LINEMATE]);
  size += sprintf(buff, " %d", cli_temp->inventory[DERAUMERE]);
  size += sprintf(buff, " %d", cli_temp->inventory[SIBUR]);
  size += sprintf(buff, " %d", cli_temp->inventory[MENDIANE]);
  size += sprintf(buff, " %d", cli_temp->inventory[PHIRAS]);
  size += sprintf(buff, " %d", cli_temp->inventory[THYSTAME]);
  size += sprintf(buff, " %d", cli_temp->pos.x);
  size += sprintf(buff, " %d", cli_temp->pos.y);
  return (size);
}

t_client	*search_client(t_list **current, int n, t_env *env)
{
  t_list	*tmp;
  t_client	*client_temp;
  int		i;
  
  tmp = *current;
  while (i < env->nb_player)
    {
      client_temp = tmp->data;
      if (client_temp->socket == n)
	return (client_temp);
      tmp = tmp->next;
      i++;
    }
  return (NULL);
}
