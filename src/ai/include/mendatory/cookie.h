/*
** cookie.h for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/include/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 21:09:51 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:09:51 2017 vincent.mesquita@epitech.eu
*/

#ifndef COOKIE_H_
# define COOKIE_H_

# include <netinet/in.h>

typedef struct          e_cookie
{
    int                 fd;
    struct sockaddr_in  addr;
}               t_cookie;

int cookie_setup(t_cookie *cook);
int cookie_connect(t_cookie *cook, t_arg *arg);
int cookie_disconnect(t_cookie *cook);

#endif /* !COOKIE_H_ */
