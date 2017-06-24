/*
** commun.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:20:07 2017 Gregoire Renard
** Last update Sat Jun 24 15:29:27 2017 vincent.mesquita@epitech.eu
*/

#ifndef COMMUN_H_
#define COMMUN_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SUCCESS	1
# define ERROR		-1

typedef enum		e_resource
  {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  }			t_resource;

#endif /* !COMMUN_H_ */
