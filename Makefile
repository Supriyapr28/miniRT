NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS = -I$(INC_DIR) -I$(LIBFT_DIR)

SRC_DIR := src
INC_DIR := includes
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)

MLX_DIR := minilibx_opengl_20191021
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else

MLX_DIR := minilibx-linux
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

endif 

SRC := $(SRC_DIR)/main.c \
	$(SRC_DIR)/hooking/hook.c \
	$(SRC_DIR)/rendering/render.c \
	$(SRC_DIR)/parsing/parse_scene.c \
	$(SRC_DIR)/parsing/parse_elements.c \
	$(SRC_DIR)/parsing_utils/ambient_utils.c \
	$(SRC_DIR)/parsing/parse_types.c \
	$(SRC_DIR)/parsing/parse_lines.c \
	$(SRC_DIR)/parsing/parse_line_utils.c \
	$(SRC_DIR)/error_handler/parse_error.c \
	$(SRC_DIR)/garbage_collector/free_scene.c \
	$(SRC_DIR)/garbage_collector/free_tokens.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(MLX_LIB) -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
