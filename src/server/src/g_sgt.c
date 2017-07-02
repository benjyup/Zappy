/*
** g_sgt.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 11:40:30 2017 Gregoire Renard
** Last update Sun Jul  2 11:40:31 2017 Gregoire Renard
*/

#include "server.h"

int	g_sgt(t_env *env, t_client *client, t_list **current)
{
  char	buff[18];

  (void)current;
  sprintf(buff, "sgt %d\n", env->arg.freq);
  my_send(client, buff, 0);
  return (SUCCESS);
}

int	g_sst(t_env *env, t_client *client, t_list **current)
{
  char	buff[18];

  (void)current;
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
