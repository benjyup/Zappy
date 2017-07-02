/*
** winner_function.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 17:47:10 2017 Gregoire Renard
** Last update Sun Jul  2 18:04:08 2017 Gregoire Renard
*/

#include "server.h"

static char	*who_is_winner(t_env *env)
{
  int		cpt;

  cpt = 0;
  while (cpt != env->arg.nb_team)
    {
      if (env->arg.team[cpt].nb_player != 0)
	return (env->arg.team[cpt].team_name);
      cpt++;
    }
  return (NULL);
}

t_bool			winner_function(t_env *env,
					int client_socket)
{
  (void)client_socket;
  g_seg(env, who_is_winner(env));
  return (true);
}
