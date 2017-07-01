#include "server.h"

int             g_pex(t_client *client, t_env *env)
{
  char          buff[32];

  sprintf(buff, "pex %d\n", client->socket);
  send_graphical(&env->clients->next, env, buff, 0);
  return (SUCCESS);
}

int             g_pbc(t_client *client, t_env *env, char *str)
{
  char          *buff;

  if ((buff = malloc(32 + strlen(str))) == NULL)
    {
      perror(MALLOC);
      exit(-1);
    }
  sprintf(buff, "pbc %d\n", client->socket);
  send_graphical(&env->clients->next, env, buff, 0);
  return (SUCCESS);
}

int             g_pfk(t_client *client, t_env *env)
{
  char          buff[32];

  sprintf(buff, "pfk %d\n", client->socket);
  send_graphical(&env->clients->next, env, buff, 0);
  return (SUCCESS);
}

int		g_enw(t_client *client, t_env *env, int num_egg)
{
  char		buff[64];

  sprintf(buff, "enw %d %d %d %d\n", num_egg, client->socket,
	  client->pos.x, client->pos.y);
  send_graphical(&env->clients->next, env, buff, 42 / env->arg.freq);
  return (SUCCESS);
}

int		g_eht(t_client *client, t_env *env, int num_egg)
{
  char		buff[32];

  (void)client;
  sprintf(buff, "eht %d\n", num_egg);
  send_graphical(&env->clients->next, env, buff, (600 + 42) / env->arg.freq);
  return (SUCCESS);
}
