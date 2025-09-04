# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by user              #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.

# Mandatory sources
MANDATORY_SOURCES = pipex.c \
					utils.c \
					process.c \
					path.c

# Bonus sources
BONUS_SOURCES = pipex_bonus.c \
				multiple_pipes.c \
				execute_commands.c \
				here_doc.c \
				bonus_utils.c \
				get_next_line.c

# Object files
MANDATORY_OBJS = $(addprefix mandatory/, $(MANDATORY_SOURCES:.c=.o))
BONUS_OBJS = $(addprefix bonus/, $(BONUS_SOURCES:.c=.o))

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(MANDATORY_OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) -Llibft -lft -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(BONUS_OBJS) -Llibft -lft -o $(BONUS_NAME)

mandatory/%.o: mandatory/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus/%.o: bonus/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re