# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 21:35:31 by zytrams           #+#    #+#              #
#    Updated: 2019/09/28 12:35:34 by fsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

GAME_FILES =	freefps.c

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
				sound.c

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
