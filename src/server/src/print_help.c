/*
** print_help.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue Jun 20 11:36:45 2017 Gregoire Renard
** Last update Tue Jun 27 19:00:54 2017 Gregoire Renard
*/

#include "server.h"

int			print_help(int ret)
{
  printf("USAGE: ./zappy_server -p port -x width ");
  printf("-y height -n name1 name2 ...  -c clientsNb -f freq\n");
  printf("\tport\t\tis the port number\n");
  printf("\twidth\t\tis the width of the world\n");
  printf("\theight\t\tis the height of the world\n");
  printf("\tnameX\t\tis the name of the team X\n");
  printf("\tclientsNb\tis the number of authorized clients per team\n");
  printf("\tfreq\t\tis the reciprocal of time ");
  printf("unit for execution of actions\n");
  return (ret);
}
