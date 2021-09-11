CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

DIR_LIBFT = libft
NAME_LIBFT = libft.a
DIR_SRCS = srcs
DIR_INC = include
DIR_BUILD = build

SRCS =	main.c \
		validator.c \
		parser.c \
		execute_commands.c \
		pipe.c \
		pipex_utils.c \
		redirections.c \
		implemented_utils.c \
		implemented.c \
		implemented_2.c \
		parser_dollar.c \
		parser_params.c \
		parser_additional.c \
		my_signals.c \
		map.c \
		pipe_child.c \
		pipe_2.c \

SRC = $(addprefix $(DIR_SRCS)/, $(SRCS))

OBJ = $(SRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)

all: lib $(NAME)

lib:
	$(MAKE) bonus -C $(DIR_LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -I$(DIR_INC) -I$(DIR_LIBFT) -c $< -o $@

-include $(DEP)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lft -L$(DIR_LIBFT) -lreadline

clean:
	rm -rf $(OBJ) $(DEP)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(DIR_LIBFT)

re: fclean all

.PHONY: all clean fclean re
