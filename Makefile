##
## Makefile for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myirc
## 
## Made by Gregoire Renard
## Login   <renard_e@epitech.net>
## 
## Started on  Mon May 22 08:49:41 2017 Gregoire Renard
## Last update Mon Jun 12 09:15:14 2017 Gregoire Renard
##

CC		=	gcc -Iinclude/ -g3

RM		=	rm -fr

SRCS_AI		=	src/ai/main.c

OBJS_AI		=	$(SRCS_AI:.c=.o)

SRCS_SERVER	=	src/server/main.c

OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)

SERVER_NAME	=	zappy_server

AI_NAME		=	zappy_ai

CFLAGS		=	-W -Wall -Werror -Wextra

all		:	zappy_server zappy_ai

re		:	fclean all

zappy_server	:	$(OBJS_SERVER)
			$(CC) -o $(SERVER_NAME) $(SRCS_SERVER)

zappy_ai	:	$(OBJS_AI)
			$(CC) -o $(AI_NAME) $(SRCS_AI)

clean		:
			$(RM) $(OBJS_AI)
			$(RM) $(OBJS_SERVER)

fclean		:	clean
			$(RM) $(SERVER_NAME)
			$(RM) $(AI_NAME)

.PHONY		: all re clean fclean
