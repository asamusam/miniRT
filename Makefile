# BIN = bin
# NAME = miniRT
# CC = cc
# CFLAG = -Wall -Werror -Wextra -g3
# #SRC_PATH = ./src/
# # SRC = $(wildcard $(SRC_PATH)*.c)
# SRC = src/close.c \
# 	  src/color.c \
# 	  src/image.c \
# 	  src/init.c \
# 	  src/main.c
# # why not just $(SRC:.c=.o)?
# OBJ = $(SRC:src/%c=$(BIN)/%o)
# INCS = includes
# LIBFT_PATH = libft
# # probably, $(LIBFT_PATH)/$(LIBFT_NAME) where LIBFT_NAME = libft.a
# LIBFT = $(LIBFT_PATH)
# # what is ft?
# LFLAGS = -L$(LIBFT) -lft -L$(MLX_PATH)
# IFLAGS = -I$(INCS) -I$(LIBFT_PATH) -I$(MLX_PATH)
# UNAME := $(shell uname)
# MLX_PATH = minilibx-linux
# MLX_NAME = libmlx_Linux.a
# MLX = $(MLX_PATH)$(MLX_NAME)
# RM = rm -rf

# ifeq ($(UNAME), Darwin)
# 	CC = gcc
# 	LFLAGS += -lmlx -framework OpenGL -framework Appkit
# #FreeBSD
# else ifeq ($(UNAME), FreeBDS)
# 	CC = clang
# 	LFLAGS += -lmlx -lbsd -lXext -lX11 -lm
# else
# 	CC = gcc
# 	CFLAG += -D Linux
# 	LFLAGS += -lmlx_Linux -lbsd -lXext -lX11 -lm
# # I have linux at home and it doesn't compile this way for some reason, but compiles with -L/usr/lib -lXext -lX11 -lm -lz
# endif

# all: $(MLX) $(NAME)

# $(BIN)/%.o: src/%.c
# 	$(CC) -c $< $(CFLAG) $(IFLAGS) -o $@

# $(NAME): $(BIN) $(OBJ) | $(LIBFT)
# 	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

# $(MLX):
# 	@git submodule init
# 	@git submodule update
# 	@make -sC $(MLX_PATH)

# $(BIN):
# 	mkdir -p $(BIN)

# $(LIBFT):
# 	@make all -C $(LIBFT_PATH) --no-print-directory

# clean:
# 	$(RM) $(BIN)

# fclean: clean
# 	$(RM) $(NAME)
# 	@make fclean -C $(LIBFT_PATH) --no-print-directory

# re: fclean all

# # ./map/map.ber
# test:
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME) ./map/map.ber

# show:
# 	@printf "UNAME		: $(UNAME)\n"
# 	@printf "NAME		: $(NAME)\n"
# 	@printf "CC			: $(CC)\n"
# 	@printf "CFLAG		: $(CFLAG)\n"
# 	@printf "LFLAGS		: $(LFLAGS)\n"
# 	@printf "IFLAGS		: $(IFLAGS)\n"
# 	@printf "SRC		: $(SRC)\n"
# 	@printf "OBJS		: $(OBJS)\n"

# # why libft is there?
# .PHONY: all clean fclean re $(LIBFT)


CFLAGS := -Wall -Wextra -Werror
LFLAGS := -L/usr/lib -lXext -lX11 -lm -lz
INCLUDE := -Iincludes -Iminilibx-linux -Ilibft
LIBFT := libft/libft.a
MINILIBX := minilibx-linux/libmlx_Linux.a
CFILES := src/main.c src/init.c src/close.c src/color.c src/image.c \
		  src/parser.c src/parser_utils.c src/parser_shapes.c src/parser_errors.c src/ft_atof.c
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
