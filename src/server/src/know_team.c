/*
** know_team.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 26 13:06:07 2017 Gregoire Renard
** Last update Mon Jun 26 14:42:00 2017 Gregoire Renard
*/

#include "server.h"

void		know_team(t_env *env, t_client *client)
{
  if ((strcmp("GRAPHIC", client->cmd)) == 0)
    {
      client->type = monitor;
      client->name_team = "GRAPHIC";
    }
  else
    add_to_the_team(env, client);
}
