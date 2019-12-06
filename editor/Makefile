# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 17:18:06 by djast             #+#    #+#              #
#    Updated: 2019/12/06 20:50:19 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_EDITOR = editor

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

LIBFT_FOLDER = ./libft
LIBFT = $(LIBFT_FOLDER)/libft.a
LIBFT_HEADER = $(LIBFT_FOLDER)/libft.h

ID_UN := $(shell id -un)

SDL_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/include/SDL2
SDL_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/lib

SDL_TTF_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2
SDL_TTF_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/lib

SDL_MIXER_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2
SDL_MIXER_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/lib

HEADERS_DIRECTORY = ./includes
HEADERS_EDITOR = $(HEADERS_DIRECTORY)/editor.h

LIBS = -lft -L$(LIBFT_FOLDER) -L$(SDL_TTF_LIB) -L$(SDL_MIXER_LIB) -L$(SDL_LIB)  -lSDL2 -lSDL2_ttf -lSDL2_mixer
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_FOLDER) -I$(SDL_TTF_FOLDER) -I$(SDL_MIXER_FOLDER) -I$(SDL_FOLDER)

EDITOR_FILES =	editor.c \
				draw.c \
				redraw.c \
				draw_sidebar.c \
				draw_buttons0.c \
				draw_buttons1.c \
				draw_buttons2.c \
				draw_input_field.c \
				draw_headline.c \
				draw_grid.c \
				init_grid.c \
				bigloop.c \
				events.c \
				clicks.c \
				take_a_lap.c \
				save_wall.c \
				points_of_sect.c \
				cut_the_rope.c \
				remover.c \
				put_stuff.c \
				commands.c \
				utils.c \
				init.c \
				check_intersect_l.c \
				check_intersect_r.c \
				check_local_intersects.c \
				check_the_touch.c \
				check_overlays.c \
				save_map.c \
				save_utils.c \
				status_text.c \
				write_to_file.c \
				write_objects.c \
				write_vertexes.c \
				clockwise.c

SRC_DIRECTORY = ./sources/
SRC_DIRECTORY_EDITOR = $(SRC_DIRECTORY)editor/

SRC_EDITOR_FILES = $(addprefix $(SRC_DIRECTORY_EDITOR), $(EDITOR_FILES))

OBJ_FILES_EDITOR = $(patsubst %.c, %.o, $(EDITOR_FILES))

OBJ_DIRECTORY = ./objects/
OBJ_DIRECTORY_EDITOR = $(OBJ_DIRECTORY)editor/

OBJ_EDITOR_FILES = $(addprefix $(OBJ_DIRECTORY_EDITOR), $(OBJ_FILES_EDITOR))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME_EDITOR)

$(NAME_EDITOR): $(LIBFT) $(OBJ_DIRECTORY) $(OBJ_DIRECTORY_EDITOR) $(OBJ_EDITOR_FILES)
	@echo -n '.'
# 	@echo "$(RED)$(NAME_EDITOR) $(GREEN)compiled successfully!$(RESET)"

$(OBJ_DIRECTORY):
	@mkdir -p $(OBJ_DIRECTORY)

$(OBJ_DIRECTORY_WOLF3D):
	@mkdir -p $(OBJ_DIRECTORY_WOLF3D)

$(OBJ_DIRECTORY_EDITOR):
	@mkdir -p $(OBJ_DIRECTORY_EDITOR)

$(OBJ_DIRECTORY_EDITOR)%.o : $(SRC_DIRECTORY_EDITOR)%.c $(HEADERS_WOLF3D) $(HEADERS_EDITOR)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo -n '.'

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_FOLDER)
# 	@echo "$(RED)Libft $(GREEN)compiled successfully!$(RESET)"

clean:
	@$(MAKE) -sC $(LIBFT_FOLDER) clean
	@/bin/rm -rf $(OBJ_EDITOR_FILES)
# 	@echo "$(RED)Libft $(GREEN)object files were deleted!$(RESET)"
# 	@echo "$(RED)Object $(GREEN)files deleted.$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_FOLDER) fclean
	@/bin/rm -rf $(NAME_EDITOR)
# 	@echo "$(RED)Libft.a $(GREEN)was deleted.$(RESET)"
# 	@echo "$(RED)$(NAME_EDITOR) $(GREEN)was deleted.$(RESET)"

re: fclean all
