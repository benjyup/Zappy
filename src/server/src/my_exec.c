/*
** my_exec.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:55:30 2017 vincent.mesquita@epitech.eu
** Last update Thu Jun 22 14:57:40 2017 Gregoire Renard
*/

#include <string.h>
#include "server.h"
#include "commands.h"

int             my_exec(t_env *env,
			t_client *client,
			t_list **current)
{
  int		i;

  i = 0;
  if (!(client->split_cmd = my_str_to_wordtab(client->cmd, ' ')))
    return (ERROR);
  while (i < NBR_OF_COMMANDS)
    {
      if (strcasecmp(exec_array[i].flag, client->split_cmd[0]) == 0)
	{
	  exec_array[i].exec(env, client, current);
	  return (SUCCESS);
	}
      i += 1;
    }
  my_send(client, KO);
  my_free_wordtab(client->split_cmd);
  return (ERROR);
}
