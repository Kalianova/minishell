NAME = minishell
CFLAGS = -Wall -Werror -Wextra
DIR_LIBFT = ./libft
NAME_LIBFT = libft.a

SRC =	main.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re bonus

%.o: %.c
	gcc $(CFLAGS) -I. -I$(DIR_LIBFT) -c $< -o $@

$(NAME):
	$(MAKE) -C $(DIR_LIBFT)
	cp libft/libft.a $(NAME)

all: $(NAME):

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(DIR_LIBFT)

re: fclean all: $(NAME)
