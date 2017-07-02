/*
** cookie.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/src/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 20:51:10 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:06:01 2017 vincent.mesquita@epitech.eu
*/

#include <mendatory/argument.h>
#include <mendatory/cookie.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <zconf.h>

static void		print_ip(struct hostent *hostinfo,
				 char *host)
{
  struct in_addr	**addr_list;
  int i;

  i = 0;
  addr_list = (struct in_addr **)hostinfo->h_addr_list;
  printf("%s: %s IP's is ", name, host);
  while (addr_list[i] != NULL)
    {
      printf("%s", inet_ntoa(*addr_list[i]));
      i += 1;
    }
  printf("\n");
}

int			cookie_connect(t_cookie *cook,
				       t_arg *arg)
{
  struct hostent	*hostinfo;

  hostinfo = gethostbyname(arg->host);
  if (hostinfo == NULL)
    return (perror("gethostbyname()"), 1);
  cook->addr.sin_addr.s_addr =
    inet_addr(inet_ntoa(*(struct in_addr*)hostinfo->h_addr));
  cook->addr.sin_port = htons(arg->port);
  cook->addr.sin_family = AF_INET;
  if (connect(cook->fd,
	      (const struct sockaddr *)&cook->addr,
	      sizeof(cook->addr)) == -1)
    return (perror("connect()"), 1);
  return (0);
}

int			cookie_disconnect(t_cookie *cook)
{
  if (cook->fd != -1)
    if (close(cook->fd) == -1)
      return (perror("close()"), 1);
  return (0);
}

int			cookie_setup(t_cookie *cook)
{
  struct protoent	*pe;

  if (!(pe = getprotobyname("TCP")))
    return (perror("getprotobyname():"), 1);
  cook->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (cook->fd == -1)
    return (perror("socket()"), 1);
  return (0);
}
