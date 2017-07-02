/*
** my_send.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Wed Jun 21 14:43:04 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 19:23:02 2017 Gregoire Renard
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		my_send(t_client *client,
			char *message,
			double time_action)
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
  msg->time_action = time_action;
  my_add_to_end(client->to_write, msg);
}

static void	check_end_incant(t_env *env, t_client *client)
{
  if ((check_end_incante(env, client)) == ERROR)
    {
      client->level--;
      my_send(client, KO, 0);
    }
  else
    up_all_player(env, client);
}

static void	time_calculation(t_client *client,
				 t_msg *msg,
				 t_list *current,
				 t_env *env)
{
  client->rst_time_unit -= msg->time_action;
  if (client->type != monitor &&
      client->name_team != NULL && client->rst_time_unit <= 0)
    {
      client->rst_time_unit = env->time_one_unit;
      if (msg->time_action == 300 / env->arg.freq)
	client->inventory[FOOD]--;
      client->inventory[FOOD]--;
    }
  if (client->incantation == 1)
    check_end_incant(env, client);
  client->incantation = 0;
  client->action = 0;
  if ((msg->current_index =
       write(client->socket,
	     &msg->msg[msg->current_index], msg->length))
      == (ssize_t)msg->length)
    {
      free(msg->msg);
      free(current->data);
      my_del_elem(client->to_write, current, NULL);
    }
}

void		my_send_to_client(t_client *client,
				  t_env *env)
{
  t_list	*current;
  t_msg		*msg;

  if ((current = client->to_write->next) == client->to_write)
    return ;
  msg = current->data;
  if (msg->time_action == 0 ||
      (time(NULL) - client->time_start) >= msg->time_action)
    time_calculation(client, msg, current, env);
}
