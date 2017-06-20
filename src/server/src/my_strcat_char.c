/*
** my_strcat_char.c for my_strcat_char in /home/mesqui_v/rendu/Minishell1/PSU_2015_minishell1
**
** Made by vincent mesquita
** Login   <mesqui_v@epitech.net>
**
** Started on  Fri Jan  8 16:01:57 2016 vincent mesquita
** Last update Mon Jun 19 22:55:00 2017 vincent.mesquita@epitech.eu
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

char		*my_strcat_char(char *str, char c)
{
  char		*cpy;
  int		i;

  i = 0;
  if (str == NULL)
    {
      if ((cpy = malloc(2 * sizeof(char))) == NULL)
	return (NULL);
      cpy[0] = c;
      cpy[1] = 0;
      return (cpy);
    }
  if (c == 0)
    return (str);
  if ((cpy = malloc((strlen(str) + 2) * sizeof(char))) == NULL)
    return (NULL);
  while (str[i])
    {
      cpy[i] = str[i];
      i = i + 1;
    }
  cpy[i] = c;
  cpy[i + 1] = 0;
  free(str);
  return (cpy);
}

char		*my_strcat_char_env(char *str, char c)
{
  char		*cpy;
  int		i;

  i = 0;
  if (str == NULL)
    {
      if ((cpy = malloc(2 * sizeof(char))) == NULL)
	return (NULL);
      cpy[0] = c;
      cpy[1] = 0;
      return (cpy);
    }
  if (c == 0)
    return (str);
  if ((cpy = malloc((strlen(str) + 2) * sizeof(char))) == NULL)
    return (NULL);
  while (str[i])
    {
      cpy[i] = str[i];
      i = i + 1;
    }
  cpy[i] = c;
  cpy[i + 1] = 0;
  return (cpy);
}
