# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 21:35:31 by zytrams           #+#    #+#              #
#    Updated: 2019/08/26 18:22:52 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = freefps
CC = gcc
FLAGS =

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./lib/libft/
LIBFT_DIRECTORY_HEADERS = $(LIBFT_DIRECTORY)includes

GAME_SRCS_LIST = freefps.c \

SDL = $(SDL_DIRECTORY)libmlx.a
SDL_DIRECTORY = ./lib/sdl2/
SDL_INCLUDES = ./engine/includes/SDL2/

GAME_OBJS_DIRECTORY = ./game/objs/
GAME_SRCS_DIRECTORY = ./game/srcs/

GAME_HEADERS_DIRECTORY = ./game/includes/
GAME_HEADERS_LIST = game.h
GAME_HEADERS = $(addprefix $(GAME_HEADERS_DIRECTORY), $(GAME_HEADERS_LIST))
GAME_INCLUDES = -I$(GAME_HEADERS_DIRECTORY)

GAME_SRCS = $(addprefix $(GAME_SRCS_DIRECTORY), $(GAME_SRCS_LIST))

GAME_OBJS = $(addprefix $(GAME_OBJS_DIRECTORY), $(GAME_OBJS_LIST))

GAME_OBJS_LIST = $(patsubst %.c, %.o, $(GAME_SRCS_LIST))

ENGINE_SRCS_LIST =	error_handler.c \
					utility.c \
					parser.c \
					engine.c \
					draw.c \
					objects.c \
					rasterizer.c \
					bresenham.c \
					color.c \
					normal.c \
					images.c \
					texture.c \

ENGINE_OBJS_DIRECTORY = ./engine/objs/
ENGINE_SRCS_DIRECTORY = ./engine/srcs/

ENGINE_HEADERS_DIRECTORY = ./engine/includes/
ENGINE_HEADERS_LIST = engine.h
ENGINE_HEADERS = $(addprefix $(ENGINE_HEADERS_DIRECTORY), $(ENGINE_HEADERS_LIST))
ENGINE_INCLUDES = -I $(ENGINE_HEADERS_DIRECTORY)

ENGINE_SRCS = $(addprefix $(ENGINE_SRCS_DIRECTORY), $(ENGINE_SRCS_LIST))

ENGINE_OBJS = $(addprefix $(ENGINE_OBJS_DIRECTORY), $(ENGINE_OBJS_LIST))

ENGINE_OBJS_LIST = $(patsubst %.c, %.o, $(ENGINE_SRCS_LIST))

all: $(NAME)

$(NAME): $(LIBFT) $(ENGINE_OBJS_DIRECTORY) $(ENGINE_OBJS) $(GAME_OBJS_DIRECTORY) $(GAME_OBJS)
	$(CC) -o $(NAME) $(GAME_OBJS) $(ENGINE_OBJS) -I $(SDL_INCLUDES) -L $(SDL_DIRECTORY) $(LIBFT) -g -l SDL2-2.0.0 -lm

$(ENGINE_OBJS_DIRECTORY):
	mkdir -p $(ENGINE_OBJS_DIRECTORY)
	echo "$(NAME): $(ENGINE_OBJS_DIRECTORY) was created"

$(ENGINE_OBJS_DIRECTORY)%.o: $(ENGINE_SRCS_DIRECTORY)%.c $(ENGINE_HEADERS)
	$(CC) $(FLAGS) -c $(ENGINE_INCLUDES) -I $(SDL_INCLUDES) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_DIRECTORY) $< -o $@ -g

$(GAME_OBJS_DIRECTORY):
	mkdir -p $(GAME_OBJS_DIRECTORY)
	echo "$(NAME): $(GAME_OBJS_DIRECTORY) was created"

$(GAME_OBJS_DIRECTORY)%.o: $(GAME_SRCS_DIRECTORY)%.c $(GAME_HEADERS)
	$(CC) $(FLAGS) -c $(GAME_INCLUDES) -I $(ENGINE_HEADERS_DIRECTORY) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_DIRECTORY) $< -o $@ -g

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	rm -rf $(GAME_OBJS_DIRECTORY)/*.o
	rm -rf $(ENGINE_OBJS_DIRECTORY)/*.o
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean


fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean

re: fclean all
