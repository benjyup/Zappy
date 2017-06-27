/*
** write_component.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 27 13:32:11 2017 Gregoire Renard
** Last update Tue Jun 27 19:01:14 2017 Gregoire Renard
*/

#include "server.h"

static int	add_resource(t_env *env, t_look *look,
			     int indic)
{
  int		cpt;

  cpt = 0;
  while (cpt != MAX_RESOURCE)
    {
      if (env->map[look->tmp.y][look->tmp.x].resource[cpt] != 0)
	{
	  if ((look->message = realloc(look->message,
				       strlen(look->message)
				       + strlen(env->resources[cpt])
				       + 3)) == NULL)
	    return (ERROR);
	  if (indic != 0)
	    strcat(look->message, " ");
	  strcat(look->message, env->resources[cpt]);
	  strcat(look->message, "\0");
	  indic = 1;
	}
      cpt++;
    }
  return (SUCCESS);
}

int		write_component(t_look *look,
				t_env *env)
{
  int		cpt;

  cpt = 0;
  while (env->map[look->tmp.y][look->tmp.x].clients[cpt] != NULL)
    {
      if ((look->message = realloc(look->message,
				   strlen(look->message)
				   + 8)) == NULL)
	return (ERROR);
      if (cpt == 0)
	strcat(look->message, "player");
      else
	strcat(look->message, " player");
      strcat(look->message, "\0");
      cpt++;
    }
  if ((add_resource(env, look, cpt)) == ERROR)
    return (ERROR);
  if ((look->message = realloc(look->message,
			       strlen(look->message) + 2)) == NULL)
    return (ERROR);
  strcat(look->message, ",\0");
  return (SUCCESS);
}
