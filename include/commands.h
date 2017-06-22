/*
** commands.h for  in /home/vincent/rendu/MyIRC/PSU_2016_myirc/server
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Fri Jun  2 17:01:05 2017 vincent.mesquita@epitech.eu
** Last update Thu Jun 22 16:59:23 2017 Gregoire Renard
*/

#ifndef COMMANDS_H_
# define COMMANDS_H_

# include "server.h"

# define NBR_OF_COMMANDS 11

# define FORWARD	"Forward"
# define RIGHT		"Right"
# define LEFT		"Left"
# define LOOK		"Look"
# define INVENTORY	"Inventory"
# define BROADCAST	"Broadcast"
# define CONNECT_NBR	"Connect_nbr"
# define FORK		"Fork"
# define EJECT		"Eject"
# define TAKE		"Take"
# define SET		"Set"
# define INCANTATION	"Incantation"
# define MSZ		"msz "
# define BCT		"bct "
# define TNA		"tna"
# define PPO		"ppo"
# define PLV		"plv"
# define PIN		"pin"

int     g_msz(t_env *env, t_client *client, t_list **current);
int     g_bct(t_env *env, t_client *client, t_list **current);
int     g_mct(t_env *env, t_client *client, t_list **current);
int     g_tna(t_env *env, t_client *client, t_list **current);
int     g_ppo(t_env *env, t_client *client, t_list **current);
int     g_plv(t_env *env, t_client *client, t_list **current);
int     g_pin(t_env *env, t_client *client, t_list **current);


typedef int		(*t_exec_cmd)(t_env *env,
				      t_client *client,
				      t_list **current);

typedef struct		s_cmd
{
  char			*flag;
  t_exec_cmd		exec;
  t_client_type		client_type;
}			t_cmd;

static t_cmd		exec_array[NBR_OF_COMMANDS] = {
  {"msz", g_msz, monitor},
  {"bct", g_bct, monitor},
  {"mct", g_mct, monitor},
  {"tna", g_tna, monitor},
  {"ppo", g_ppo, monitor},
  {"plv", g_plv, monitor},
  {"pin", g_pin, monitor},
  
  {FORWARD, &forward_func, player},
  {RIGHT, &right_func, player},
  {LEFT, &left_func, player},
  {CONNECT_NBR, &connect_nbr_func, player}
};

#endif /* !COMMANDS_H_ */
