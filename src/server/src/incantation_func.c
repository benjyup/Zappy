/*
** incantation_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri Jun 30 14:59:18 2017 Gregoire Renard
** Last update Sun Jul  2 19:23:26 2017 Gregoire Renard
*/

#include "server.h"

static int	strlen_clients(t_client **client)
{
  int		cpt;

  cpt = 0;
  while (client[cpt] != NULL)
    cpt++;
  return (cpt);
}

static void	send_message_elevation(t_client *client, t_env *env)
{
  char		*message;
  char		*level;

  level = to_string(client->level);
  if ((message = strdup(INCAN_UNDER)) == NULL
      || (message = realloc(message, strlen(message) + 10)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  strcat(message, level);
  strcat(message, "\n\0");
  my_send(client, message, 0);
  my_send(client, "", 300 / env->arg.freq);
  free(message);
  free(level);
  client->incantation = 1;
}

static void	check_conditions(t_env *env, t_client *client)
{
  int		nb_player;
  int		cpt;
  int		stop;

  cpt = 1;
  stop = 0;
  nb_player = strlen_clients(env->map[client->pos.y][client->pos.x].clients);
  if (nb_player != env->elevation[client->level - 1].nb_player)
    my_send(client, KO, 0);
  while (cpt != MAX_RESOURCE && stop != 1)
    {
      if (env->map[client->pos.y][client->pos.x].resource[cpt]
	  != env->elevation[client->level - 1].needed_res[cpt])
	stop = 1;
      cpt++;
    }
  if (stop == 1)
    my_send(client, KO, 0);
  else
    {
      send_message_elevation(client, env);
      g_pic(env, client, &env->clients->next);
      client->level++;
    }
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
