##
## Makefile for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myirc
## 
## Made by Gregoire Renard
## Login   <renard_e@epitech.net>
## 
## Started on  Mon May 22 08:49:41 2017 Gregoire Renard
## Last update Mon Jun 19 18:09:41 2017 vincent.mesquita@epitech.eu
##

CC		=	gcc -Iinclude/ -g3

RM		=	rm -fr

SRCS_AI		=	src/ai/main.c

OBJS_AI		=	$(SRCS_AI:.c=.o)

AI_NAME		=	zappy_ai

SERVER_PATH	=	./src/server/

CFLAGS		=	-W -Wall -Werror -Wextra

all		:	zappy_server zappy_ai

re		:	fclean all

zappy_server	:
			make  -C $(SERVER_PATH)

zappy_ai	:	$(OBJS_AI)
			$(CC) -o $(AI_NAME) $(SRCS_AI)

clean		:
			$(RM) $(OBJS_AI)
			make  clean -C $(SERVER_PATH)

fclean		:	clean
			make  fclean -C $(SERVER_PATH)
			$(RM) $(AI_NAME)

.PHONY		: all re clean fclean
