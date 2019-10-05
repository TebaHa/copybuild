# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 21:35:31 by zytrams           #+#    #+#              #
#    Updated: 2019/10/03 12:01:12 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME = freefps
#CC = gcc
#FLAGS =
#
#
#LIBFT = $(LIBFT_DIRECTORY)libft.a
#LIBFT_DIRECTORY = ./lib/libft/
#LIBFT_DIRECTORY_HEADERS = $(LIBFT_DIRECTORY)includes
#
#GAME_SRCS_LIST =	freefps.c \
#					weapon_fire.c \
#
#SDL = $(SDL_DIRECTORY)libmlx.a
#SDL_DIRECTORY = ./lib/sdl2/
#SDL_INCLUDES = ./engine/includes/SDL2/
#
#SDL_TTF_DIRECTORY = -L ./lib/sdl_ttf/
#
#GAME_OBJS_DIRECTORY = ./game/objs/
#GAME_SRCS_DIRECTORY = ./game/srcs/
#
#GAME_HEADERS_DIRECTORY = ./game/includes/
#GAME_HEADERS_LIST = game.h
#GAME_HEADERS = $(addprefix $(GAME_HEADERS_DIRECTORY), $(GAME_HEADERS_LIST))
#GAME_INCLUDES = -I$(GAME_HEADERS_DIRECTORY)
#
#GAME_SRCS = $(addprefix $(GAME_SRCS_DIRECTORY), $(GAME_SRCS_LIST))
#
#GAME_OBJS = $(addprefix $(GAME_OBJS_DIRECTORY), $(GAME_OBJS_LIST))
#
#GAME_OBJS_LIST = $(patsubst %.c, %.o, $(GAME_SRCS_LIST))
#
#ENGINE_SRCS_LIST =	error_handler.c \
#					utility.c \
#					parser.c \
#					parser_resources.c \
#					parser_errors.c \
#					parser_filler.c \
#					parser_reader.c \
#					parser_utility.c \
#					parser_utility_find.c \
#					parser_enemy.c \
#					parser_weapon.c \
#					parser_hud_face.c \
#					parser_items.c \
#					parser_hud.c \
#					engine.c \
#					draw.c \
#					objects.c \
#					rasterizer.c \
#					bresenham.c \
#					color.c \
#					normal.c \
#					images.c \
#					texture.c \
#					hud_draw.c \
#					shoot.c \
#					relative_coord.c \
#					animator.c \
#					zbuff.c \
#
#ENGINE_OBJS_DIRECTORY = ./engine/objs/
#ENGINE_SRCS_DIRECTORY = ./engine/srcs/
#
#ENGINE_HEADERS_DIRECTORY = ./engine/includes/
#ENGINE_HEADERS_LIST = engine.h
#ENGINE_HEADERS = $(addprefix $(ENGINE_HEADERS_DIRECTORY), $(ENGINE_HEADERS_LIST))
#ENGINE_INCLUDES = -I $(ENGINE_HEADERS_DIRECTORY)
#
#ENGINE_SRCS = $(addprefix $(ENGINE_SRCS_DIRECTORY), $(ENGINE_SRCS_LIST))
#
#ENGINE_OBJS = $(addprefix $(ENGINE_OBJS_DIRECTORY), $(ENGINE_OBJS_LIST))
#
#ENGINE_OBJS_LIST = $(patsubst %.c, %.o, $(ENGINE_SRCS_LIST))
#
#all: $(NAME)
#
#$(NAME): $(LIBFT) $(ENGINE_OBJS_DIRECTORY) $(ENGINE_OBJS) $(GAME_OBJS_DIRECTORY) $(GAME_OBJS)
#	$(CC) -Ofast -O3 -o $(NAME) $(GAME_OBJS) $(ENGINE_OBJS) -I $(SDL_INCLUDES) -L $(SDL_DIRECTORY) $(SDL_TTF_DIRECTORY) $(LIBFT) -l SDL2-2.0.0 -lm
#
#$(ENGINE_OBJS_DIRECTORY):
#	mkdir -p $(ENGINE_OBJS_DIRECTORY)
#	echo "$(NAME): $(ENGINE_OBJS_DIRECTORY) was created"
#
#$(ENGINE_OBJS_DIRECTORY)%.o: $(ENGINE_SRCS_DIRECTORY)%.c $(ENGINE_HEADERS)
#	$(CC) -Ofast -O3 $(FLAGS) -c $(ENGINE_INCLUDES) -I $(SDL_INCLUDES) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_DIRECTORY) $< -o $@
#
#$(GAME_OBJS_DIRECTORY):
#	mkdir -p $(GAME_OBJS_DIRECTORY)
#	echo "$(NAME): $(GAME_OBJS_DIRECTORY) was created"
#
#$(GAME_OBJS_DIRECTORY)%.o: $(GAME_SRCS_DIRECTORY)%.c $(GAME_HEADERS)
#	$(CC) -Ofast -O3 $(FLAGS) -c $(GAME_INCLUDES) -I $(ENGINE_HEADERS_DIRECTORY) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_DIRECTORY) $< -o $@
#$(LIBFT):
#	$(MAKE) -sC $(LIBFT_DIRECTORY)
#
#clean:
#	rm -rf $(GAME_OBJS_DIRECTORY)/*.o
#	rm -rf $(ENGINE_OBJS_DIRECTORY)/*.o
#	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
#
#
#fclean: clean
#	@rm -rf $(NAME)
#	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
#
#re: fclean all

NAME_DOOM_NUKEM = DoomNukem
#NAME_EDITOR = Editor

CC = gcc
FLAGS = -Wall -Wextra -Werror -O3 -Ofast

ID_UN := $(shell id -un)

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

LIBFT_FOLDER = ./lib/libft/
LIBFT = $(LIBFT_FOLDER)libft.a
LIBFT_HEADER_FOLDER = $(LIBFT_FOLDER)/includes
LIBFT_HEADER = $(LIBFT_FOLDER)/includes/libft.h

SDL_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/include/SDL2
SDL_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/lib

SDL_TTF_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2
SDL_TTF_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/lib

SDL_MIXER_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2
SDL_MIXER_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/lib

GAME_HEADERS_DIRECTORY = ./game/includes/
GAME_HEADERS = $(GAME_HEADERS_DIRECTORY)/game.h

ENGINE_HEADERS_DIRECTORY = ./engine/includes/
ENGINE_HEADERS = $(ENGINE_HEADERS_DIRECTORY)/engine.h

LIBS = -lft -L$(LIBFT_FOLDER) -L$(SDL_TTF_LIB) -L$(SDL_MIXER_LIB) \
		-L$(SDL_LIB) -lSDL2 -lSDL2_ttf -lSDL2_mixer
INCLUDES = -I$(GAME_HEADERS_DIRECTORY) -I$(ENGINE_HEADERS_DIRECTORY) \
		-I$(LIBFT_HEADER_FOLDER) -I$(SDL_TTF_FOLDER) -I$(SDL_MIXER_FOLDER) \
		-I$(SDL_FOLDER)

GAME_FILES =	freefps.c \
				weapon_fire.c

ENGINE_FILES =	utility.c \
				error_handler.c \
				parser.c \
				parser_resources.c \
				parser_errors.c \
				parser_filler.c \
				parser_reader.c \
				parser_utility.c \
				parser_utility_find.c \
				parser_enemy.c \
				parser_weapon.c \
				parser_hud_face.c \
				parser_items.c \
				parser_hud.c \
				engine.c \
				draw.c \
				objects.c \
				rasterizer.c \
				bresenham.c \
				color.c \
				normal.c \
				images.c \
				texture.c \
				hud_draw.c \
				shoot.c \
				relative_coord.c \
				animator.c \
				zbuff.c
#				sound.c

SRC_DIRECTORY_GAME = ./game/srcs/
SRC_DIRECTORY_ENGINE = ./engine/srcs/

SRC_GAME_FILES = $(addprefix $(SRC_DIRECTORY_GAME), $(GAME_FILES))
SRC_ENGINE_FILES = $(addprefix $(SRC_DIRECTORY_ENGINE), $(ENGINE_FILES))

OBJ_FILES_GAME = $(patsubst %.c, %.o, $(GAME_FILES))
OBJ_FILES_ENGINE = $(patsubst %.c, %.o, $(ENGINE_FILES))

OBJ_DIRECTORY = ./objects/
OBJ_DIRECTORY_GAME = $(OBJ_DIRECTORY)game/
OBJ_DIRECTORY_ENGINE = $(OBJ_DIRECTORY)engine/

OBJ_GAME_FILES = $(addprefix $(OBJ_DIRECTORY_GAME), $(OBJ_FILES_GAME))
OBJ_ENGINE_FILES = $(addprefix $(OBJ_DIRECTORY_ENGINE), $(OBJ_FILES_ENGINE))

all: $(NAME_DOOM_NUKEM)

$(NAME_DOOM_NUKEM): $(LIBFT) $(OBJ_DIRECTORY) $(OBJ_DIRECTORY_GAME) $(OBJ_GAME_FILES) $(OBJ_DIRECTORY_ENGINE) $(OBJ_ENGINE_FILES)
	@$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) $(OBJ_GAME_FILES) $(OBJ_ENGINE_FILES) -o $(NAME_DOOM_NUKEM)
	@echo "$(RED)$(NAME_DOOM_NUKEM) $(GREEN)compiled successfully!$(RESET)"

#$(NAME_EDITOR): $(LIBFT) $(OBJ_DIRECTORY) $(OBJ_DIRECTORY_EDITOR) $(OBJ_EDITOR_FILES)
#	@$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) $(OBJ_EDITOR_FILES)  -o $(NAME_EDITOR)
#	@echo "$(RED)$(NAME_EDITOR) $(GREEN)compiled successfully!$(RESET)"

$(OBJ_DIRECTORY):
	@mkdir -p $(OBJ_DIRECTORY)

$(OBJ_DIRECTORY_GAME):
	@mkdir -p $(OBJ_DIRECTORY_GAME)

$(OBJ_DIRECTORY_ENGINE):
	@mkdir -p $(OBJ_DIRECTORY_ENGINE)

$(OBJ_DIRECTORY_GAME)%.o : $(SRC_DIRECTORY_GAME)%.c $(GAME_HEADERS) $(ENGINE_HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJ_DIRECTORY_ENGINE)%.o : $(SRC_DIRECTORY_ENGINE)%.c $(GAME_HEADERS) $(ENGINE_HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_FOLDER)
	@echo "$(RED)Libft $(GREEN)compiled successfully!$(RESET)"

clean:
	@$(MAKE) -sC $(LIBFT_FOLDER) clean
	@echo "$(RED)Libft $(GREEN)object files were deleted!$(RESET)"
	@/bin/rm -rf $(OBJ_GAME_FILES)
	@/bin/rm -rf $(OBJ_ENGINE_FILES)
	@/bin/rm -rf $(OBJ_DIRECTORY)
	@echo "$(RED)Object $(GREEN)files deleted.$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_FOLDER) fclean
	@echo "$(RED)Libft.a $(GREEN)was deleted.$(RESET)"
	@/bin/rm -rf $(NAME_DOOM_NUKEM)
	@echo "$(RED)$(NAME_DOOM_NUKEM) $(GREEN)was deleted.$(RESET)"

re: fclean all
