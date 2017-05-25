# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 14:08:11 by vrybalko          #+#    #+#              #
#    Updated: 2017/05/25 22:25:11 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

IDIR = includes/

VPATH = src:includes

BIN_DIR = bin/

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	USE_F = X11
endif
ifeq ($(UNAME_S),Darwin)
	USE_F = MLX
endif

FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit

FLAGS_X11 = -pthread -lmlx -lXext -lX11 -lm

LIB = libft/libft.a

SRCS = main.c								\
       ft_hooks.c						\
       ft_hooks1.c					\
			 ft_img_px_put.c			\
			 ft_mlx_events.c			\
			 ft_mlx_init.c				\
			 ray_tools.c					\
			 ray_tools1.c					\
			 ray_tools2.c					\
			 ray_tools3.c					\
			 ray_tools4.c					\
			 ray_tools5.c					\
			 render.c							\
			 render1.c						\
			 scene.c							\
			 sphere.c							\
			 sphere1.c						\
			 cylinder.c						\
			 cylinder1.c					\
			 cone.c								\
			 cone1.c							\
			 disk.c								\
			 disk1.c							\
			 color.c							\
			 color1.c							\
			 plane.c							\
			 plane1.c							\
			 read_file.c					\
			 read_cone.c					\
			 read_cyl.c						\
			 read_sphere_plane.c	\
			 read_file_utils.c		\
			 textures.c						\
			 get_color.c					\
			 material.c						\
			 camera.c							\
			 quaternion.c					\
			 quaternion1.c				\
			 quaternion2.c				\

BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BINS)
	make -C libft/
	gcc -o $(NAME) $(BINS) $(FLAGS) $(FLAGS_$(USE_F)) $(LIB)

$(BIN_DIR)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	make -C libft/ clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

anti_alias:
	/bin/rm -f bin/render.o
	gcc $(FLAGS) -DSAMPLES=2 -c -o bin/render.o src/render.c
	gcc -o $(NAME) $(BINS) $(FLAGS) $(FLAGS_$(USE_F)) $(LIB)
