BIN = bin
NAME = miniRT
CC = cc
CFLAG = -Wall -Werror -Wextra -g3
SRC := src/close.c \
		src/color.c \
		src/color_calc.c \
		src/color_utils.c \
		src/cylinder_utils.c \
		src/debug.c \
		src/ft_atof.c \
		src/image.c \
		src/init.c \
		src/init_cylinder.c \
		src/init_plane.c \
		src/init_sphere.c \
		src/init_world.c \
		src/intersections.c \
		src/light.c \
		src/light_utils.c \
		src/main.c \
		src/math_utils.c \
		src/matrix.c \
		src/matrix_transform.c \
		src/matrix_utils.c \
		src/parser.c \
		src/parser_errors.c \
		src/parser_range.c \
		src/parser_shapes.c \
		src/parser_utils.c \
		src/print_scene.c \
		src/ray.c \
		src/render.c \
		src/shapes.c \
		src/tuples.c \
		src/tuple_calc.c \
		src/tuples_utils.c \
		src/world_utils.c
OBJ = $(patsubst src/%c,$(BIN)/%o,$(SRC))
INCS = includes
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)
LFLAGS = -L$(LIBFT) -lft -L$(MLX_PATH)
IFLAGS = -I$(INCS) -I$(LIBFT_PATH) -I$(MLX_PATH)
UNAME := $(shell uname)
MLX_PATH = minilibx-linux
MLX_NAME = libmlx_Linux.a
MLX = $(MLX_PATH)$(MLX_NAME)
RM = rm -rf

ifeq ($(UNAME), Darwin)
	CC = gcc
	LFLAGS += -lmlx -framework OpenGL -framework Appkit
else ifeq ($(UNAME), FreeBSD)
	CC = clang
	LFLAGS += -lmlx -lbsd -lXext -lX11 -lm
else
	CC = gcc
	CFLAG += -D Linux
	LFLAGS += -lmlx_Linux -lXext -lX11 -lm
endif

all: $(MLX) $(NAME)

$(BIN)/%.o: src/%.c
	$(CC) -c $< $(CFLAG) $(IFLAGS) -o $@

$(NAME): $(BIN) $(OBJ) | $(LIBFT)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

$(MLX):
	@git submodule init
	@git submodule update
	-@make -C $(MLX_PATH)

$(BIN):
	mkdir -p $(BIN)

$(LIBFT):
	@make all -C $(LIBFT_PATH) --no-print-directory

clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re: fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME) ./scenes/sphere_scene2.rt

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME		: $(NAME)\n"
	@printf "CC			: $(CC)\n"
	@printf "CFLAG		: $(CFLAG)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "IFLAGS		: $(IFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJS		: $(OBJS)\n"

.PHONY: all clean fclean re $(LIBFT)
