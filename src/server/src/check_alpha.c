/*
** check_alpha.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 14:49:26 2017 Gregoire Renard
** Last update Tue Jun 20 18:33:08 2017 Gregoire Renard
*/

#include "server.h"

int		check_alpha(char *str)
{
  int		cpt;

  cpt = 0;
  while (str[cpt] != '\0')
    {
      if (str[cpt] < '0' || str[cpt] > '9')
	return (ERROR);
      if (cpt >= 9)
	return (ERROR);
      cpt++;
    }
  return (SUCCESS);
}
