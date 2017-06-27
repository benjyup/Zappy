/*
** my_xdprintf.c for  in /home/kyxo/rendu/Reseau/PSU_2016_myirc/serv/src
** 
** Made by Vincent
** Login   <florian.vincent@epitech.eu>
** 
** Started on  Sat Jun 10 17:30:14 2017 Vincent
** Last update Tue Jun 27 19:03:14 2017 Gregoire Renard
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

void		build_string(char *str, va_list *ap, char *f, int i)
{
  int		j;
  char		nbr[10];

  j = 0;
  while (f[i])
    {
      if (f[i] == '%' && f[i + 1] == 's')
	{
	  str[j] = 0;
	  strcat(str, va_arg(*ap, char *));
	  j = strlen(str);
	  i += 2;
	}
      else if (f[i] == '%' && f[i + 1] == 'l' && f[i + 2] == 'u')
	{
	  str[j] = 0;
	  sprintf(nbr, "%lu", va_arg(*ap, unsigned long));
	  strcat(str, nbr);
	  j = strlen(str);
	  i += 3;
	}
      else
	str[j++] = f[i++];
    }
  str[j] = 0;
}

int		xdprintf(int fd, t_msg *msg, va_list *ap)
{
  char		*str;
  int		wrote;

  printf("xdprintf %s\n", msg->msg);
  if (!msg->msg || (str = malloc(512)) == NULL)
    return (0);
  str[0] = 0;
  build_string(str, ap, msg->msg, 0);
  msg->length = strlen(str);
  wrote = dprintf(fd, "%s", str);
  printf("j'ai écrit %d\n", wrote);
  free(str);
  return (wrote);
}
