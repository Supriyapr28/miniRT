# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/03 12:00:06 by spaipur-          #+#    #+#              #
#    Updated: 2026/09/16 11:15:24 by uvadakku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS = -I. -I$(INC_DIR) -I$(LIBFT_DIR)

SRC_DIR := src
INC_DIR := includes
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
MLX_DIR := minilibx_opengl_20191021
MLX_REPO := https://github.com/42Paris/minilibx-mac.git
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
MLX_DIR := minilibx-linux
MLX_REPO := https://github.com/42Paris/minilibx-linux.git
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
endif

SRC := $(SRC_DIR)/ray_tracer.c \
	$(SRC_DIR)/hooking/key_handler.c \
	$(SRC_DIR)/hooking/object_key_handler.c \
	$(SRC_DIR)/hooking/mouse_handler.c \
	$(SRC_DIR)/hooking/reset_handler.c \
	$(SRC_DIR)/rendering/render_scene.c \
	$(SRC_DIR)/camera/camera_move.c \
	$(SRC_DIR)/camera/camera_rotate.c \
	$(SRC_DIR)/draw_func_window/draw_axes.c \
	$(SRC_DIR)/draw_func_window/draw_axes_objects.c \
	$(SRC_DIR)/draw_func_window/draw_axes_labels.c \
	$(SRC_DIR)/draw_func_window/draw_axes_line.c \
	$(SRC_DIR)/parsing/parse_scene.c \
	$(SRC_DIR)/parsing/parse_elements.c \
	$(SRC_DIR)/parsing/parse_line.c \
	$(SRC_DIR)/parsing/parse_objects.c \
	$(SRC_DIR)/parsing_utils/parse_types_utils.c \
	$(SRC_DIR)/parsing_utils/parse_types_utils2.c \
	$(SRC_DIR)/error_handler/parse_error.c \
	$(SRC_DIR)/garbage_collector/free_scene.c \
	$(SRC_DIR)/garbage_collector/destroy_window.c \
	$(SRC_DIR)/validation/parse_object_validation.c \
	$(SRC_DIR)/validation/parse_scene_validation.c \
	$(SRC_DIR)/utils/vec3_math.c \
	$(SRC_DIR)/utils/vec3_math1.c \
	$(SRC_DIR)/utils/object_transform.c \
	$(SRC_DIR)/utils/object_state.c \
	$(SRC_DIR)/rendering/cast_ray.c \
	$(SRC_DIR)/rendering/hit_sphere.c \
	$(SRC_DIR)/rendering/hit_cylinder.c \
	$(SRC_DIR)/rendering/hit_cyl_helper.c \
	$(SRC_DIR)/rendering/find_hit.c \
	$(SRC_DIR)/rendering/lighting.c \
	$(SRC_DIR)/rendering/lighting_utils.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) mlx
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(MLX_LIB) -o $@

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
        echo "→ MiniLibX not found. Downloading..."; \
        git clone $(MLX_REPO) $(MLX_DIR); \
    fi

mlx: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c | $(MLX_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
