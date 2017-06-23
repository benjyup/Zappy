/*
** server.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:19:50 2017 Gregoire Renard
** Last update Fri Jun 23 12:48:49 2017 Gregoire Renard
*/

#ifndef SERVER_H_
#define SERVER_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdarg.h>
# include "commun.h"

# define VALUE		i + h + 1
# define MALLOC		"malloc"
# define NBR_OF_ARGS	6
# define SOCKET_PROTOCOL "TCP"
# define BUFFLENGTH	513
# define END_OF_CMD	'\n'
# define MAX_CMD	6
# define MAX_RESOURCE	7
# define MAX_PLAYER	10

# define KO		"ko\n"
# define WELCOME	"welcome\n"
# define OK		"ok\n"

typedef struct		s_pos
{
  int			x;
  int			y;
}			t_pos;

typedef enum		e_bool
  {
    false = 0,
    true
  }			t_bool;

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

typedef enum		e_client_type
  {
    player = 0,
    monitor
  }			t_client_type;

typedef struct		s_list
{
  void		*data;
  struct s_list	*prev;
  struct s_list	*next;
}			t_list;

typedef	struct		s_team
{
  char			*team_name;
  int			nb_player;
}			t_team;

typedef	struct		s_arg
{
  int			port;
  int			width;
  int			height;
  t_team		*team;
  int			nb_team;
  int			clients_lim;
  int			freq;
}			t_arg;

typedef	struct		s_map
{
  char			*name_team;
  int			*fd_player;
  int			resource[MAX_RESOURCE];
  int			border;
}			t_map;

typedef struct		s_env
{
  t_arg			arg;
  int			time;
  int			socket;
  int                   highest_fd;
  unsigned long		current_client_id;
  fd_set		readf;
  fd_set		writef;
  socklen_t		struct_length;
  struct sockaddr_in	info;
  struct protoent	*pe;
  t_list		*clients;
  t_map			**map;
  char			**resources;
  int			nb_player;
}			t_env;

typedef	struct		s_pointer
{
  char			*opt;
  int			(*func)(t_env *env,
				char **argv,
				int *cpt);
}			t_pointer;

typedef struct		s_client
{
  int                   socket;
  char                  cmd[BUFFLENGTH + 1];
  char                  **split_cmd;
  unsigned long		id;
  t_list		*this;
  int			inventory[MAX_RESOURCE];
  t_pos			pos;
  t_pos			dir;
  char			*name_team;
  t_list		*to_write;
}			t_client;

typedef struct		s_msg
{
  char			*msg;
  unsigned int		length;
  ssize_t		current_index;
}			t_msg;


typedef void(free_callback)(void *data);

int			xdprintf(int fd,
				 t_msg *msg,
				 va_list *ap);
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
char			*my_strcat_char(char *str1,
					char c);
char			**my_str_to_wordtab(char *str,
					    char separator);
void			my_free_wordtab(char **wordtab);
int			my_exec(t_env *env,
				t_client *client,
				t_list **current);
int			print_help(int ret);
int			init_arg(t_env *env, char **argv);
int			printf_error(char *str);
int			check_opt(char **argv,
				  int *cpt,
				  t_env *env,
				  t_pointer *pointer);
int			opt_p(t_env *env,
			      char **argv,
			      int *cpt);
int			opt_x(t_env *env,
			      char **argv,
			      int *cpt);
int			opt_y(t_env *env,
			      char **argv,
			      int *cpt);
int			opt_n(t_env *env,
			      char **argv,
			      int *cpt);
int			opt_c(t_env *env,
			      char **argv,
			      int *cpt);
int			opt_f(t_env *env,
			      char **argv,
			      int *cpt);
int			check_alpha(char *str);
int			init_map(t_env *env);
void			print_map(t_env *env);
void			add_to_the_team(t_env *env, t_client *client);
void			my_send_to_client(t_client *client);
void			my_send(t_client *client,
				char *message);
char			*to_string(int nb);
int			forward_func(t_env *env, t_client *client,
				     t_list **current);
void			erase_in_map(t_env *env, t_client *client);
void			add_in_map(t_env *env, t_client *client);
int			right_func(t_env *env, t_client *client,
				   t_list **current);
int			left_func(t_env *env, t_client *client,
				  t_list **current);
int			connect_nbr_func(t_env *env, t_client *client,
					 t_list **current);
int			inventory_func(t_env *env, t_client *client,
				       t_list **current);
void			init_env_resources(t_env *env);

#endif /* !SERVER_H_ */
