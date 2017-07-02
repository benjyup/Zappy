/*
** server.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon Jun 12 09:19:50 2017 Gregoire Renard
** Last update Sun Jul  2 19:22:20 2017 Gregoire Renard
*/

#ifndef SERVER_H_
#define SERVER_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdarg.h>
# include <time.h>
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
# define MAX_LEVEL	7

# define KO		"ko\n"
# define WELCOME	"welcome\n"
# define OK		"ok\n"
# define SUC		"suc\n"
# define DEAD		"dead\n"
# define INCAN_UNDER	"Elevation underway\nCurrent level: "

typedef	struct		s_client t_client;

typedef struct		s_elevation
{
  int			nb_player;
  int			needed_res[MAX_RESOURCE];
}			t_elevation;

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

typedef enum		e_client_type
  {
    player = 0,
    monitor,
    egg,
    none
  }			t_client_type;

typedef struct		s_list
{
  void		*data;
  struct s_list	*prev;
  struct s_list	*next;
}			t_list;

typedef	struct		s_eggs
{
  t_pos			pos;
  int			time;
  int			id;
}			t_eggs;

typedef	struct		s_team
{
  char			*team_name;
  t_list		*eggs;
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
  t_client		**clients;
  int			resource[MAX_RESOURCE];
  int			border;
}			t_map;

typedef struct		s_env
{
  t_arg			arg;
  float			time_one_unit;
  int			time_food;
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
  int			nb_eggs;
  t_elevation		elevation[MAX_LEVEL];
  int			real_start;
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
  int			level;
  t_client_type		type;
  int			time_start;
  int			action;
  int			time_unit;
  float			rst_time_unit;
  int			incantation;
}			t_client;

typedef	struct		s_look
{
  int			range;
  char			*message;
  int			cpt;
  t_pos			tmp;
  t_pos			target;
}			t_look;

typedef struct		s_msg
{
  char			*msg;
  unsigned int		length;
  ssize_t		current_index;
  double		time_action;
}			t_msg;

typedef	struct		s_broad
{
  t_pos			dir;
  t_pos			tmp;
}			t_broad;

typedef void(free_callback)(void *data);

int			xdprintf(int fd,
				 t_msg *msg,
				 va_list *ap);
t_bool			init_server(t_env *env);
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
int			add_to_the_team(t_env *env, t_client *client,
					t_pos new_pos);
void			my_send_to_client(t_client *client, t_env *env);
void			my_send(t_client *client,
				char *message,
				double time_action);
char			*to_string(int nb);
t_client		*search_client(t_list **current, int n, t_env *env);
int			def_dir(t_client *client);

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
int			look_func(t_env *env, t_client *client,
				  t_list **current);
int			broadcast_func(t_env *env, t_client *client,
				       t_list **current);
int			g_msz(t_env *env, t_client *client, t_list **current);
int			g_bct(t_env *env, t_client *client, t_list **current);
int			g_mct(t_env *env, t_client *client, t_list **current);
int			g_tna(t_env *env, t_client *client, t_list **current);
int			g_ppo(t_env *env, t_client *client, t_list **current);
int			g_plv(t_env *env, t_client *client, t_list **current);
int			g_pin(t_env *env, t_client *client, t_list **current);
int			get_size_map(int x, int y, t_env *env);
int			get_size(t_client *cli_temp, int n);
int			g_sbp(t_client *client);
void			send_graphical(t_list **current,
				       t_env *env, char *str, int time);
void			know_team(t_env *env, t_client *client);
int			g_pnw(t_env *env, t_client *client, t_list **current);
int			set_func(t_env *env, t_client *client, t_list **current);
int			take_func(t_env *env, t_client *client, t_list **current);
int			g_pdr(t_env *env, t_client *client,
			      t_list **current, int ress);
int			g_pgt(t_env *env, t_client *client,
			      t_list **current, int ress);
void			set_new_pos_f(t_env *env, t_client *client,
				      t_pos *new_pos);
void			set_new_pos_l(t_env *env, t_client *client,
				      t_pos *new_pos);
void			set_new_pos_r(t_env *env, t_client *client,
				      t_pos *new_pos);
int			eject_func(t_env *env, t_client *client, t_list **current);
int			forward_eject(t_env *env, t_client *client, t_pos *dir);
void			send_to_all_user(t_env *env, t_pos pos,
					 t_client *client, char *message);
int			write_component(t_look *look, t_env *env);
void			set_pos_start(t_env *env, t_client *client,
				      t_look *look);
int		        fork_func(t_env *env, t_client *client, t_list **current);
int			g_sst(t_env *env, t_client *client, t_list **current);
int			g_sgt(t_env *env, t_client *client, t_list **current);
int			g_pbc(t_client *client, t_env *env, char *str);
int			g_pex(t_client *client, t_env *env);
int			g_pfk(t_client *client, t_env *env);
int			g_enw(t_client *client, t_env *env, int num_egg);
int			g_eht(t_client *client, t_env *env, int num_egg);
void			g_ebo(t_env *env, int id_egg);
void			pop_food(t_env *env);
void			check_func(t_env *env, t_client *client,
				   t_list **current);
void			check_timer_client(t_env *env, t_client *client,
					   t_list **current);
void			init_elevation(t_env *env);
int			incantation_func(t_env *env,
					 t_client *client,
					 t_list **current);
void			init_level1(t_env *env);
void			init_level2(t_env *env);
void			init_level3(t_env *env);
void			init_level4(t_env *env);
void			init_level5(t_env *env);
void			init_level6(t_env *env);
void			init_level7(t_env *env);
void			init_new_client(t_client **client, t_env *env);
void			g_seg(t_env *env, char *winner);
int			grep_number(char **message);
void			check_all_map(t_env *env, t_client *client,
				      char **message);
int			horizontal_port(t_client *sender,
					t_client *receiver);
int			vertical_port(t_client *sender,
				      t_client *receiver);
int			border_port(t_client *sender,
				    t_client *receiver);
int			g_pic(t_env *env, t_client *client, t_list **current);
int			g_pie(t_env *env, t_client *client, t_list **current, int res);
int			g_pdi(t_client *client, t_env *env);
t_bool			winner_function(t_env *env, char *team);
int			check_end_incante(t_env *env, t_client *client);
void			up_all_player(t_env *env, t_client *client);

#endif /* !SERVER_H_ */
