/*
** commun.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:20:07 2017 Gregoire Renard
** Last update Mon Jun 19 17:56:25 2017 vincent.mesquita@epitech.eu
*/

#ifndef COMMUN_H_
#define COMMUN_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SUCCESS	1
# define ERROR		-1

typedef enum		e_bool
  {
    false = 0,
    true
  }			t_bool;

typedef struct		s_list
{
  void		*data;
  struct s_list	*prev;
  struct s_list	*next;
}			t_list;

typedef struct		s_serv_env
{

}			t_serv_env;

int			xdprintf(int fd,
				 char *format, ...);

#endif /* !COMMUN_H_ */
