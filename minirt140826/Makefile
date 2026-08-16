# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguillen <gguillen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/16 09:03:21 by gguillen          #+#    #+#              #
#    Updated: 2026/08/16 09:07:28 by gguillen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directorios
RENDER_DIR   = render
FORMS_DIR    = forms
MATHS_DIR    = maths
PARSING_DIR  = parsing
INCLUDES_DIR = includes

CFLAGS += -I$(INCLUDES_DIR)

# Detección de sistema operativo
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    MLX_DIR = minilibx
    CFLAGS += -I$(MLX_DIR)
    LDFLAGS = -L$(MLX_DIR) -Wl,-rpath,@executable_path/$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    MLX_LIB = $(MLX_DIR)/libmlx.dylib
else
    MLX_DIR = minilibx-linux
    CFLAGS += -I$(MLX_DIR)
    LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
    MLX_LIB = $(MLX_DIR)/libmlx.a
endif

SRCS_RENDER = camera.c color.c minirt.c render.c render_1.c

SRCS_FORMS = cylindre.c plan.c sphere.c

SRCS_MATHS = lambert.c maths_0.c maths_1.c

SRCS_PARSE = parse_main.c parse_main_1.c parse_line.c \
             parse_elements_0.c parse_elements_1.c parse_elements_2.c \
             parse_values_0.c parse_values_1.c parse_values_2.c \
             parse_values_3.c parse_values_4.c \
             parse_utils_0.c parse_utils_1.c parse_free.c parse_setup.c

SRCS = $(addprefix $(RENDER_DIR)/, $(SRCS_RENDER)) \
       $(addprefix $(FORMS_DIR)/, $(SRCS_FORMS)) \
       $(addprefix $(MATHS_DIR)/, $(SRCS_MATHS)) \
       $(addprefix $(PARSING_DIR)/, $(SRCS_PARSE))

OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re