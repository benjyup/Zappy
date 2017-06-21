##
## Makefile for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_zappy/src/server
## 
## Made by Gregoire Renard
## Login   <renard_e@epitech.net>
## 
## Started on  Tue Jun 20 10:56:10 2017 Gregoire Renard
## Last update Wed Jun 21 17:18:02 2017 Gregoire Renard
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
		src/server.c \
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

