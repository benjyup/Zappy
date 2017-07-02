##
## Makefile for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myirc
## 
## Made by Gregoire Renard
## Login   <renard_e@epitech.net>
## 
## Started on  Mon May 22 08:49:41 2017 Gregoire Renard
## Last update Sun Jul  2 21:26:32 2017 vincent.mesquita@epitech.eu
##

CC		=	gcc -Iinclude/ -g3

RM		=	rm -fr

AI_PATH		=	./src/ai/

SERVER_PATH	=	./src/server/

CFLAGS		=	-W -Wall -Werror -Wextra

all		:	zappy_server zappy_ai

re		:	fclean all

zappy_server	:
			make -C $(SERVER_PATH)

zappy_ai	:
			make -C $(AI_PATH)

clean		:
			make  clean -C $(SERVER_PATH)
			make  clean -C $(AI_PATH)

fclean		:
			make  fclean -C $(SERVER_PATH)
			make  fclean -C $(AI_PATH)

.PHONY		: all re clean fclean
