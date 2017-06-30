#include "server.h"

void		g_ebo(t_env *env, int id_egg)
{
  char		buff[32];

  sprintf(buff, "ebo %d\n", id_egg);
  send_graphical(&env->clients->next, env, buff, 0);
}
