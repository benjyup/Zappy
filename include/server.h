/*
** server.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:19:50 2017 Gregoire Renard
** Last update Mon Jun 19 22:46:30 2017 vincent.mesquita@epitech.eu
*/

#ifndef SERVER_H_
#define SERVER_H_

# include "commun.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define MALLOC		"malloc"
# define NBR_OF_ARGS	6
# define SOCKET_PROTOCOL "TCP"
# define BUFFLENGTH	513
# define END_OF_CMD	'\n'

typedef enum		e_bool
  {
    false = 0,
    true
  }			t_bool;

typedef enum e_client_type
  {
    player = 0,
    monitor
  }	     t_client_type;

typedef struct		s_list
{
  void		*data;
  struct s_list	*prev;
  struct s_list	*next;
}			t_list;

typedef struct		s_env
{
  int			port;
  int			socket;
  int                   highest_fd;
  unsigned long		current_client_id;
  fd_set		readf;
  fd_set		writef;
  socklen_t		struct_length;
  struct sockaddr_in	info;
  struct protoent	*pe;
  t_list		*clients;
}			t_env;

typedef struct                  s_client
{
  int                   socket;
  char                  cmd[BUFFLENGTH + 1];
  char                  **split_cmd;
  unsigned long		id;
  t_list		*this;
  FILE			*stream;
}                               t_client;

typedef void(free_callback)(void *data);

int			xdprintf(int fd,
				 char *format, ...);
t_bool			my_init_server(t_env *env);
t_bool			my_zappy_server(t_env *env);
t_list			*my_init_list(void);
t_bool			my_add_to_end(t_list *root,
				      void *data);
void			my_del_elem(t_list *root,
				    t_list *elem_to_del,
				    free_callback *data_free);
void			my_free_list(t_list *root,
				     free_callback *data_free);
int			my_select(int nfds, fd_set *readfds,
				  fd_set *writefds);
void			my_init_select(t_env *env);
void			my_close(t_client *client,
				 t_env *env);
int                     my_quit(t_env *env,
				t_client *client,
				t_list **current);

#endif /* !SERVER_H_ */
