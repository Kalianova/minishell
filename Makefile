CC = gcc
NAME = minishell
DIR_LIBFT = libft
NAME_LIBFT = libft.a

CFLAGS = -Wall -Werror -Wextra


SRC =	main.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: lib $(NAME)

lib:
	$(MAKE) bonus -C $(DIR_LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(DIR_LIBFT) -c $< -o $@
	$(CC) -MM $(CFLAGS) -I. -I$(DIR_LIBFT) $< > $*.d

-include $(OBJ:.o=.d)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lft -L$(DIR_LIBFT)

clean:
	rm -rf $(OBJ) $(DEP)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(DIR_LIBFT)

re: fclean all

.PHONY: all clean fclean re