/*
** incantation_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 14:59:18 2017 Gregoire Renard
** Last update Fri Jun 30 17:05:19 2017 Gregoire Renard
*/

#include "server.h"

/* static int	strlen_clients(t_client **client) */
/* { */
/*   int		cpt; */

/*   cpt = 0; */
/*   while (client[cpt] != NULL) */
/*     cpt++; */
/*   return (cpt); */
/* } */

void		check_conditions(t_env *env, t_client *client)
{
  (void)env;
  (void)client;
}

int		incantation_func(t_env *env,
				 t_client *client,
				 t_list **current)
{
  (void)current;
  if (client->level <= 7)
    check_conditions(env, client);
  else
    my_send(client, KO, 0);
  return (SUCCESS);
}
