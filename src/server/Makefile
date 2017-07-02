##
## Makefile for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server
## 
## Made by Gregoire Renard
## Login   <renard_e@epitech.net>
## 
## Started on  Tue Jun 20 10:56:10 2017 Gregoire Renard
## Last update Sun Jul  2 19:22:10 2017 Gregoire Renard
##

CC	=	gcc -I../../include -g3

RM	=	rm -fr

SRCS	=	src/main.c \
		src/my_close.c \
		src/my_exec.c \
		src/my_free_wordtab.c \
		src/my_linked_list.c \
		src/my_quit.c \
		src/my_select.c \
		src/my_strcat_char.c \
		src/my_str_to_wordtab.c \
		src/my_zappy_server.c \
		src/init_server.c \
		src/xfprintf.c \
		src/print_help.c \
		src/init_arg.c \
		src/printf_error.c \
		src/opt_func1.c \
		src/opt_func2.c \
		src/check_opt.c \
		src/check_alpha.c \
		src/init_map.c \
		src/print_map.c \
		src/add_to_the_team.c \
		src/my_send.c \
		src/to_string.c \
		src/forward_func.c \
		src/erase_in_map.c \
		src/add_in_map.c \
		src/right_func.c \
		src/left_func.c \
		src/connect_nbr_func.c \
		src/inventory_func.c \
		src/init_env_resources.c \
		src/look_func.c \
		src/broadcast_func.c \
		src/g_msz.c \
		src/g_function1.c \
		src/g_function2.c \
		src/g_function3.c \
		src/g_function4.c \
		src/know_team.c \
		src/g_pnw.c \
		src/set_func.c \
		src/take_func.c \
		src/eject_func.c \
		src/send_to_all_user.c \
		src/write_component.c \
		src/set_pos_start.c \
		src/fork_func.c \
		src/g_sgt.c \
		src/g_pex.c \
		src/g_ebo.c \
		src/pop_food.c \
		src/check_func.c \
		src/check_timer_client.c \
		src/incantation_func.c \
		src/init_elevation.c \
		src/init_level1.c \
		src/init_level2.c \
		src/init_level3.c \
		src/init_level4.c \
		src/init_level5.c \
		src/init_level6.c \
		src/init_level7.c \
		src/init_new_client.c \
		src/grep_number.c \
		src/check_all_map.c \
		src/horizontal_port.c \
		src/vertical_port.c \
		src/border_port.c \
		src/g_pic.c \
		src/winner_function.c \
		src/check_end_incant.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	../../zappy_server

CFLAGS	=	-W -Werror -Wall -Wextra

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(SRCS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all re clean fclean

