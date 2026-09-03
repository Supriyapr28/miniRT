# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/03 12:00:06 by spaipur-          #+#    #+#              #
#    Updated: 2026/09/03 12:00:09 by spaipur-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

MLX_DIR := .minilibx_opengl
MLX_TGZ := minilibx_macos_opengl.tgz
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else

MLX_DIR := .minilibx-linux
MLX_TGZ := minilibx-linux.tgz
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

endif

SRC := $(SRC_DIR)/main.c \
	$(SRC_DIR)/hooking/hook.c \
	$(SRC_DIR)/hooking/key_handler.c \
	$(SRC_DIR)/rendering/render.c \
	$(SRC_DIR)/rendering/render_frame.c \
	$(SRC_DIR)/camera/camera.c \
	$(SRC_DIR)/camera/camera_move.c \
	$(SRC_DIR)/camera/camera_rotate.c \
	$(SRC_DIR)/parsing/parse_scene.c \
	$(SRC_DIR)/parsing/parse_elements.c \
	$(SRC_DIR)/parsing/parse_line.c \
	$(SRC_DIR)/parsing/parse_objects.c \
	$(SRC_DIR)/parsing_utils/parse_types_utils.c \
	$(SRC_DIR)/parsing_utils/parse_types_utils2.c \
	$(SRC_DIR)/error_handler/parse_error.c \
	$(SRC_DIR)/garbage_collector/free_array_ambient.c \
	$(SRC_DIR)/garbage_collector/free_scene.c \
	$(SRC_DIR)/garbage_collector/free_tokens.c \
	$(SRC_DIR)/validation/parse_object_validation.c \
	$(SRC_DIR)/validation/parse_scene_validation.c \
	$(SRC_DIR)/utils/vec3_math.c \
	$(SRC_DIR)/utils/vec3_math1.c \
	$(SRC_DIR)/rendering/ray_tracer.c \
	$(SRC_DIR)/rendering/ray_sphere.c \
	$(SRC_DIR)/rendering/ray_cylinder.c \
	$(SRC_DIR)/rendering/ray_cyl_helper.c \
	$(SRC_DIR)/rendering/render_scene.c \
	$(SRC_DIR)/rendering/render_pixels.c \
	$(SRC_DIR)/rendering/lighting.c \
	$(SRC_DIR)/rendering/lighting_utils.c \
	$(SRC_DIR)/rendering/render_pl_cyl.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(MLX_DIR):
	mkdir -p $@
	tar -xzf $(MLX_TGZ) --strip-components=1 -C $@

$(NAME): $(OBJ) $(LIBFT_A) | $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(MLX_LIB) -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c | $(MLX_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
