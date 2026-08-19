# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/16 09:03:21 by gguillen          #+#    #+#              #
#    Updated: 2026/08/18 13:50:00 by gguillen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -std=gnu17

# Directories
RENDER_DIR = render
FORMS_DIR = forms
MATHS_DIR = maths
PARSING_DIR = parsing
INCLUDES_DIR = includes

# MiniLibX
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = minilibx
	MLX = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = minilibx-linux
	MLX = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

CFLAGS += -I$(INCLUDES_DIR) -I$(MLX_DIR)

# Sources
SRCS_RENDER = camera.c \
			  color.c \
			  minirt.c \
			  render.c \
			  render_1.c

SRCS_FORMS = cylindre.c \
			 plan.c \
			 sphere.c

SRCS_MATHS = lambert.c \
			 maths_0.c \
			 maths_1.c

SRCS_PARSE = parse_main.c \
			 parse_main_1.c \
			 parse_line.c \
			 parse_elements_0.c \
			 parse_elements_1.c \
			 parse_elements_2.c \
			 parse_values_0.c \
			 parse_values_1.c \
			 parse_values_2.c \
			 parse_values_3.c \
			 parse_values_4.c \
			 parse_utils_0.c \
			 parse_utils_1.c \
			 parse_free.c \
			 parse_setup.c

SRCS = $(addprefix $(RENDER_DIR)/, $(SRCS_RENDER)) \
	   $(addprefix $(FORMS_DIR)/, $(SRCS_FORMS)) \
	   $(addprefix $(MATHS_DIR)/, $(SRCS_MATHS)) \
	   $(addprefix $(PARSING_DIR)/, $(SRCS_PARSE))

OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR) CC="$(CC) -std=gnu89"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

