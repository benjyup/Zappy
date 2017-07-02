##
## Makefile for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai
## 
## Made by vincent.mesquita@epitech.eu
## Login   <vincent@epitech.net>
## 
## Started on  Sun Jul  2 19:21:51 2017 vincent.mesquita@epitech.eu
## Last update Sun Jul  2 23:13:59 2017 Vincent
##

NAME		=	../../zappy_client

CXX		=	g++

CC		=	gcc -Iinclude

CFLAGS		+=	-W -Wextra -Wall -Werror

CPPFLAGS	+=	-Iinclude -Iirrlicht-1.8.4/include -IirrKlang-64bit-1.5.0/include \
			-Iinclude/mendatory -I../../include -std=c++14 \
			-Lirrlicht-1.8.4/lib/Linux -Lirrlicht-1.8.4/lib/Linux/deepinx86_64 \
			-Lirrlicht-1.8.4/lib/Linux/useful -LirrKlang-64bit-1.5.0/bin/linux-gcc-64/

SRCS_CPP	=	./src/main.cpp 				\
			src/Zappy.cpp				\
			src/ZappyException.cpp			\
			src/Vector3d.cpp			\
			src/Sound.cpp				\
			src/Ressource.cpp			\
			src/parser.cpp				\
			src/GraphicalLib.cpp			\
			src/Eggs.cpp				\
			src/Drone.cpp				\
			src/Client.cpp				\
			src/Character.cpp			\
			src/Block.cpp				\

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
	$(CXX) -o $ $(NAME) $(OBJS_CPP) $(OBJS_C) $(CPPFLAGS) -lIrrlicht -lGL -lXxf86vm -lIrrKlang -lXext -lX11 -lXcursor -lpthread

clean:
	$(RM) $(OBJS_CPP) $(OBJS_C)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.cpp.o:
	$(CXX) $(CPPFLAGS) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
