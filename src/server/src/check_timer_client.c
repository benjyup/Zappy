/*
** check_timer_client.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 29 18:28:55 2017 Gregoire Renard
** Last update Fri Jun 30 18:14:45 2017 Gregoire Renard
*/

#include "server.h"

void		check_timer_client(t_env *env, t_client *client,
				   t_list **current)
{
  if (client->type != monitor && client->type != none)
    {
      if (client->time_unit != -1 &&
	  client->inventory[FOOD] <= 0)
	{
	  my_send(client, DEAD, 0);
	  my_send_to_client(client, env);
	  my_quit(env, client, current);
	}
      else if (client->time_unit != -1
	       && time(NULL) - client->time_unit >= env->time_one_unit)
	{
	  client->time_unit = time(NULL);
	  client->inventory[FOOD]--;
	  if (client->inventory[FOOD] <= 0)
	    {
	      my_send(client, DEAD, 0);
	      my_send_to_client(client, env);
	      g_pdi(client, env);
	      my_quit(env, client, current);
	    }
	}
    }
}
