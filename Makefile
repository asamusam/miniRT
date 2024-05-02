CFLAGS := -Wall -Wextra -Werror
LFLAGS := -L/usr/lib -lXext -lX11 -lm -lz
INCLUDE := -Iincludes -Iminilibx-linux -Ilibft
LIBFT := libft/libft.a
MINILIBX := minilibx-linux/libmlx_Linux.a
CFILES := src/main.c src/init.c src/close.c src/color.c src/image.c \
		  src/parser.c src/parser_utils.c src/parser_shapes.c src/parser_errors.c src/parser_range.c src/ft_atof.c
OFILES := $(CFILES:.c=.o)
NAME := miniRT

all: $(LIBFT) $(MINILIBX) $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) $(LIBFT) $(MINILIBX) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $^ -o $@ -g

$(LIBFT):
	@make -C libft

$(MINILIBX):
	@make -C minilibx-linux

clean:
	@make -C libft clean
	@make -C minilibx-linux clean
	rm -f $(OFILES)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(MINILIBX)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
