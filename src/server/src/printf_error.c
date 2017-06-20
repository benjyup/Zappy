/*
** printf_error.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 12:05:45 2017 Gregoire Renard
** Last update Tue Jun 20 14:43:14 2017 Gregoire Renard
*/

#include "server.h"

int		printf_error(char *str)
{
  printf("%s\n", str);
  return (ERROR);
}
