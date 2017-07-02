##
## Makefile for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai
## 
## Made by vincent.mesquita@epitech.eu
## Login   <vincent@epitech.net>
## 
## Started on  Sun Jul  2 19:21:51 2017 vincent.mesquita@epitech.eu
## Last update Sun Jul  2 20:17:33 2017 vincent.mesquita@epitech.eu
##

NAME		=	zappy_ai

CC		=	g++

CPPFLAGS	+=	-Iinclude -Iinclude/mendatory -I../../include -std=c++14

SRCS_CPP	=	./src/main.cpp 				\
			src/AIClient.cpp			\
			src/Parser.cpp				\
			src/Proxy.cpp				\
			src/Request.cpp				\
			src/Zappy.cpp				\
			src/ZappyException.cpp			\

SRCS_C		=	src/mendatory/argument.c		\
			src/mendatory/connection_manager.c	\
			src/mendatory/cookie.c			\
			src/mendatory/functionParse.c		\
			src/mendatory/my_stack.c		\
			src/mendatory/srv_read.c		\
			src/mendatory/srv_write.c		\

OBJS_CPP	=	$(SRCS_CPP:.cpp=.o)
OBJS_C		=	$(SRCS_C:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_CPP) $(OBJS_C)
	$(CC) -o $ $(NAME) $(OBJS_CPP) $(OBJS_C)

clean:
	$(RM) $(OBJS_CPP) $(OBJS_C)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
