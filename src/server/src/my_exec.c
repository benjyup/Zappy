/*
** my_exec.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun 19 22:55:30 2017 vincent.mesquita@epitech.eu
** Last update Wed Jun 28 22:57:47 2017 Gregoire Renard
*/

#include <string.h>
#include "server.h"
#include "commands.h"

static void	send_error(t_client *client)
{
  if (client->type == monitor)
    my_send(client, SUC, 0);
  else
    my_send(client, KO, 0);
  my_free_wordtab(client->split_cmd);
}

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
	  if (exec_array[i].client_type == client->type)
	    {
	      client->action = 1;
	      client->time_start = time(NULL);
	      exec_array[i].exec(env, client, current);
	      return (SUCCESS);
	    }
	  i = NBR_OF_COMMANDS;
	}
      i += 1;
    }
  send_error(client);
  return (ERROR);
}
