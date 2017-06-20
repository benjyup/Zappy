/*
** main.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:23:46 2017 Gregoire Renard
** Last update Mon Jun 19 19:10:04 2017 vincent.mesquita@epitech.eu
*/

#include <stdlib.h>
#include "server.h"

int		main(int argc, char **argv)
{
  t_env		env;

  (void)argc;
  env.port = atoi(argv[1]);
  if (!my_init_server(&env) ||
      my_zappy_server(&env))
    return (ERROR);
  printf("SERVER\n");
  return (SUCCESS);
}
