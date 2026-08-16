NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -L/usr/lib -L/usr/X11R6/lib
LIBS = -lmlx -lX11 -lXext -lm

SRCS_ORIG = camera.c color.c maths_0.c maths_1.c render.c render_1.c sphere.c \
			lambert.c cylindre.c plan.c

SRCS_PARSE = parse_main.c parse_main_1.c parse_line.c parse_elements_0.c \
			 parse_elements_1.c parse_elements_2.c parse_values_0.c \
			 parse_values_1.c parse_values_2.c parse_values_3.c parse_values_4.c \
			 parse_utils_0.c parse_utils_1.c parse_free.c parse_setup.c

SRCS = minirt.c $(SRCS_ORIG) $(SRCS_PARSE)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
