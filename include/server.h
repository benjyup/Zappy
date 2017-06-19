/*
** server.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:19:50 2017 Gregoire Renard
** Last update Mon Jun 19 18:13:31 2017 vincent.mesquita@epitech.eu
*/

#ifndef SERVER_H_
#define SERVER_H_

#include "commun.h"

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

#endif /* !SERVER_H_ */
