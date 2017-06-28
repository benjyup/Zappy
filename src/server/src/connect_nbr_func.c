/*
** connect_nbr_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu Jun 22 16:36:12 2017 Gregoire Renard
** Last update Wed Jun 28 23:05:36 2017 Gregoire Renard
*/

#include "server.h"

static void	send_nbr(t_env *env,
			 t_client *client,
			 int cpt)
{
  int		nbr;
  char		*tmp;
  int		len;

  nbr = env->arg.clients_lim - env->arg.team[cpt].nb_player;
  tmp = to_string(nbr);
  len = strlen(tmp);
  if ((tmp = realloc(tmp, len + 2)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  tmp[len] = '\n';
  tmp[len + 1] = 0;
  my_send(client, tmp, 0);
  free(tmp);
}

int		connect_nbr_func(t_env *env,
				 t_client *client,
				 t_list **list)
{
  int		cpt;

  (void)list;
  cpt = 0;
  while (cpt != env->arg.nb_team &&
	 (strcmp(client->name_team, env->arg.team[cpt].team_name)) != 0)
    cpt++;
  if (cpt != env->arg.nb_team)
    send_nbr(env, client, cpt);
  return (SUCCESS);
}
