/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/mesqui_v/rendu/Minishell1/Bootstrap/PSU_2015_my_exec
**
** Made by vincent mesquita
** Login   <mesqui_v@epitech.net>
**
** Started on  Fri Jan  8 11:19:59 2016 vincent mesquita
** Last update Tue Jun 27 19:04:04 2017 Gregoire Renard
*/

#include <stdlib.h>
#include "server.h"

static char		*my_word(char *str,
				 char separator,
				 int *i)
{
  char			*wordtab;

  wordtab = NULL;
  while (str[*i] && str[*i] != separator)
    {
      if ((wordtab = my_strcat_char(wordtab, str[*i])) == NULL)
	return (NULL);
      *i += 1;
    }
  return (wordtab);
}

static int		my_fill_wordtab(char		**wordtab,
					char		*str,
					char		separator)
{
  int			index;
  int			i;

  index = 0;
  i = 0;
  while (str[i])
    {
      if (str[i] != separator)
	{
	  if ((wordtab[index] = my_word(str, separator, &i)) == NULL)
	    return (-1);
	  index += 1;
	}
      if (str[i] != 0)
	i += 1;
    }
  return (0);
}

static int		count_the_words(char *str, char separator)
{
  int			i;
  int			word_count;

  word_count = 1;
  i = 0;
  while (str[i] && str[i] == separator)
    i = i + 1;
  while (str[i])
    {
      if (str[i] != 0 && str[i + 1] != 0 &&
	  str[i] == separator && (str[i + 1]
				  != separator))
	word_count +=  1;
      if (str[i] != 0)
	i += 1;
    }
  return (word_count);
}

void			my_init_wordtab(char **wordtab, int size)
{
  int			i;

  i = 0;
  while (i < size)
    {
      wordtab[i] = NULL;
      i += 1;
    }
}

char			**my_str_to_wordtab(char *str, char separator)
{
  char			**wordtab;
  int			word_count;

  if (str == NULL || str[0] == 0)
    return (NULL);
  word_count = count_the_words(str, separator);
  if ((wordtab = malloc((word_count + 1) * sizeof(char *))) == NULL)
    return (NULL);
  my_init_wordtab(wordtab, word_count + 1);
  if (my_fill_wordtab(wordtab, str, separator) == -1)
    return (NULL);
  wordtab[word_count] = NULL;
  return (wordtab);
}
