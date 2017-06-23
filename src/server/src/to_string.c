/*
** to_string.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed Jun 21 18:23:19 2017 Gregoire Renard
** Last update Fri Jun 23 13:07:47 2017 Gregoire Renard
*/

#include "server.h"

static int	count_len(int nb)
{
  int		len;
  int		div;

  len = 0;
  div = 1;
  while (nb / div >= 10)
    {
      div = div * 10;
      len++;
    }
  len++;
  return (len);
}

char		*to_string(int nb)
{
  int		len;
  char		*str;

  len = count_len(nb);
  if ((str = malloc(len + 1)) == NULL)
    {
      perror(MALLOC);
      exit(ERROR);
    }
  sprintf(str, "%d", nb);
  str[len] = 0;
  return (str);
}
