# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = philo

SRCS = srcs/main.c \
	srcs/free.c \
	srcs/parser.c \
	srcs/philo/routine.c \
	srcs/philo/initialization.c \
	srcs/philo/simulation.c \
	srcs/philo/watcher.c \
	srcs/philo/tools.c \
	srcs/utils/split.c \
	srcs/utils/alpha.c \
	srcs/utils/beta.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
