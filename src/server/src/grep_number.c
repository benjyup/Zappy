/*
** grep_number.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Sun Jul  2 14:30:30 2017 Gregoire Renard
** Last update Sun Jul  2 14:30:45 2017 Gregoire Renard
*/

#include "server.h"

int		grep_number(char **message)
{
  int		cpt;
  int		number;

  cpt = 0;
  while ((*message)[cpt] != '\0')
    {
      if ((*message)[cpt] >= '0' && (*message)[cpt] <= '9')
	{
	  number = (*message)[cpt] - 48;
	  return (number);
	}
      cpt++;
    }
  return (ERROR);
}
