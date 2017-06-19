/*
** my_exec.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:55:30 2017 vincent.mesquita@epitech.eu
** Last update Mon Jun 19 23:06:52 2017 vincent.mesquita@epitech.eu
*/

#include <string.h>
#include "server.h"
#include "commands.h"

void             my_exec(t_env *env,
			 t_client *client,
			 t_list **current)
{
  int		i;

  i = 0;
  if (!(client->split_cmd = my_str_to_wordtab(client->cmd, ' ')))
    return ;
  while (client->split_cmd[i])
    {
      fprintf(stderr, "[%d] = %s\n", i, client->split_cmd[i]);
      i++;
    }
  i = 0;
  while (i < NBR_OF_COMMANDS)
    {
      if (strcmp(exec_array[i].flag, client->split_cmd[0]) == 0)
	{
	  exec_array[i].exec(env, client, current);
	  return ;
	}
      i += 1;
    }
  xdprintf(client->socket, KO);
  my_free_wordtab(client->split_cmd);
}
