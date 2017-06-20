/*
** my_free_wordtab.c for my_free_wordtab in /home/mesqui_v/rendu/Minishell1/Bootstrap/PSU_2015_my_exec
**
** Made by vincent mesquita
** Login   <mesqui_v@epitech.net>
**
** Started on  Fri Jan  8 12:12:32 2016 vincent mesquita
** Last update Mon Jun 19 22:51:53 2017 vincent.mesquita@epitech.eu
*/

#include <stdlib.h>
#include "server.h"

void		my_free_wordtab(char **wordtab)
{
  unsigned int	i;

  if (wordtab == NULL)
    return ;
  i = 0;
  while (wordtab[i] != NULL)
    {
      if (wordtab[i] != NULL)
	free(wordtab[i]);
      i += 1;
    }
  free(wordtab);
}
