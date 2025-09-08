NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

SRCDIR = srcs
LIBFTDIR = libft

SRCS = $(SRCDIR)/pipex.c \
	   $(SRCDIR)/pipex_exec.c \
	   $(SRCDIR)/utils.c

LIBFT_SRCS = $(LIBFTDIR)/ft_strlen.c \
			 $(LIBFTDIR)/ft_strdup.c \
			 $(LIBFTDIR)/ft_strjoin.c \
			 $(LIBFTDIR)/ft_strncmp.c \
			 $(LIBFTDIR)/ft_strchr.c \
			 $(LIBFTDIR)/ft_split.c \
			 $(LIBFTDIR)/ft_putstr_fd.c \
			 $(LIBFTDIR)/ft_putendl_fd.c

OBJS = $(SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
