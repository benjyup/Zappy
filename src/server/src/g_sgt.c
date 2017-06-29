#include "server.h"

int	g_sgt(t_env *env, t_client *client, t_list **current)
{
  char	buff[18];

  sprintf(buff, "sgt %d\n", env->arg.freq);
  my_send(client, buff, 0);
  return (SUCCESS);
}

int	g_sst(t_env *env, t_client *client, t_list **current)
{
  char	buff[18];
  
  if (client->split_cmd[1] == NULL)
    {
      g_sbp(client);
      return (1);
    }
  env->arg.freq = atoi(client->split_cmd[1]);
  sprintf(buff, "sgt %d\n", env->arg.freq);
  my_send(client, buff, 0);
  return (SUCCESS);
}
