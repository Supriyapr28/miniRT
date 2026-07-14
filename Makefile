NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC_DIR := src
INC_DIR := includes

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
MLX_DIR := minilibx_macos_opengl/minilibx_opengl_20191021
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
MLX_DIR := minilibx-linux
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
endif

SRC := $(SRC_DIR)/main.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
