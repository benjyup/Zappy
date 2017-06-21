/*
** my_send.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Wed Jun 21 14:43:04 2017 vincent.mesquita@epitech.eu
** Last update Wed Jun 21 17:20:45 2017 vincent.mesquita@epitech.eu
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		my_send(t_client *client,
			char *message)
{
  t_msg		*msg;

  if (message == NULL)
    return ;
  if (!(msg = malloc(sizeof(*msg))) ||
      !(msg->msg = strdup(message)))
    {
      perror(MALLOC);
      exit(ERROR);
    }
  msg->current_index = 0;
  msg->length = strlen(message);
  my_add_to_end(client->to_write, msg);
}

void		my_send_to_client(t_client *client)
{
  t_list	*current;
  t_msg		*msg;
  

  if ((current = client->to_write->next) == client->to_write)
    return ;
  msg = current->data;
  if ((msg->current_index = write(client->socket, &msg->msg[msg->current_index], msg->length))
      == (ssize_t)msg->length)
    {
      free(msg->msg);
      free(current->data);
      my_del_elem(client->to_write, current, NULL);
    }
}
