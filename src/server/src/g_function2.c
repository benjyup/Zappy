/*
** g_function2.c for  zappy in /home/rene_r/Cours/Semestre_4/System_Unix/RESEAU/PSU_2016_zappy/src/server/src
** 
** Made by rodrigue rene
** Login   <rene_r@epitech.net>
** 
** Started on  Tue Jun 27 17:16:24 2017 rodrigue rene
** Last update Wed Jun 28 23:22:47 2017 Gregoire Renard
*/

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
  my_send(client, buff, 0);
  free(buff);
  return (1);
}

void		g_seg(t_env *env, char *str)
{
  char		*buff;

  if ((buff = malloc(strlen(str) + 6)) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(buff, "seg %s\n", str);
  send_graphical(&env->clients->next, env, buff, 0);
  free(buff);
}

int		g_edi(t_client *client, int egg)
{
  char		buff[32];

  sprintf(buff, "edi %d\n", egg);
  my_send(client, buff, 0);
  return (1);
}
