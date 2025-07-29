# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amugisha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 19:58:23 by amugisha          #+#    #+#              #
#    Updated: 2025/01/23 22:48:33 by amugisha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) $(LIB) main all clean fclean re

NAME = pipex

GREEN='\033[0;32m'

RED='\033[0;31m'

BRUN='\033[0;33m'

HEADER = header.h

LIB = libpipex.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I $(HEADER) -g3

SRC = ft_split.c forck.c command.c utils.c\
      redirection.c ft_strjoin.c ft_strncmp.c\
      path.c ft_strdup.c ft_strlcpy.c

OBJ = $(SRC:.c=.o)

MAIN = main.c

OBJM = $(MAIN:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):$(OBJM) $(LIB)
	@echo $(BRUN) "Compiling pipex..."
	@$(CC) $(CFLAGS) $(OBJM) -L. -l pipex -o $(NAME)
	@echo $(GREEN) "OK: pipex"

$(LIB):$(OBJ)
	@ar rcs -o $(LIB) $(OBJ)

main:$(MAIN)
	$(CC) $(CFLAGS) -o main.o -c $(MAIN)

all: $(NAME)

clean: 
	@echo $(BRUN) "Removing .o object..."
	@rm -rf $(OBJ) $(OBJM)
	@echo $(GREEN) "OK: Removing .o object"

fclean: clean
	@echo $(BRUN) "Removing pipex..."
	@rm -rf $(NAME) $(LIB)
	@echo $(GREEN) "OK: Removing pipex"

re: fclean all
