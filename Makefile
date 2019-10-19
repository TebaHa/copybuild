# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 21:35:31 by zytrams           #+#    #+#              #
#    Updated: 2019/10/19 21:41:33 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = freefps
CRC = checksum

CC = gcc
FLAGS = -march=native -m64 -Ofast -O2 -flto -funroll-loops
ID_UN := $(shell id -un)
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./lib/libft/
LIBFT_DIRECTORY_HEADERS = $(LIBFT_DIRECTORY)includes

GAME_SRCS_LIST =	freefps.c \
					weapon_fire.c \
					gravitation.c \
					game_controller_down.c \
					game_controller_up.c \
					game_movement.c \
					multi_threading.c \
					game_movement_funs.c \

SDL = $(SDL_DIRECTORY)libmlx.a
SDL_DIRECTORY = ./lib/sdl2/
SDL_INCLUDES = ./engine/includes/SDL2/

SDL_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/include/SDL2
SDL_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/lib

SDL_TTF_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2
SDL_TTF_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/lib

SDL_MIXER_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2
SDL_MIXER_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/lib

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
					parser_errors.c \
					parser_filler.c \
					parser_reader.c \
					parser_texture.c \
					parser_utility.c \
					parser_enemy.c \
					parser_weapon.c \
					parser_items.c \
					parser_hud.c \
					parser_polygone.c \
					parser_point_3d.c \
					parser_errors_2.c \
					parser_errors_3.c \
					parser_items_2.c \
					parser_sector_2.c \
					parser_sprite.c \
					parser_sprite_2.c \
					parser_object.c \
					parser_color.c \
					parser_package.c \
					close.c \
					sound_2.c \
					parser_sector.c \
					parser_player.c \
					parser_player_2.c \
					parser_worldbox.c \
					parser_world.c \
					parser_sprobject.c \
					engine.c \
					render_world.c \
					render_wall.c \
					objects.c \
					objects_help.c \
					bresenham.c \
					bresenham2.c \
					color.c \
					images.c \
					texture.c \
					hud_draw.c \
					shoot.c \
					relative_coord.c \
					sound.c \
					sort.c \
					sprite_render.c \
					sprite_render_2.c \
					render_stack.c \
					sprite_render_stack.c \
					pickup.c \
					font.c \
					checksum.c \
					intersection_funs.c \
					intersection_funs_help.c \
					render_cycle.c \
					render_cycle2.c \
					render_wall_help.c \
					render_wall2.c \
					normal.c \
					shoot_main.c \
					shoot_help.c \
					render_main.c \
					texture_math.c \
					render_particle.c \
					render_particle_2.c \

ENGINE_OBJS_DIRECTORY = ./engine/objs/
ENGINE_SRCS_DIRECTORY = ./engine/srcs/

ENGINE_HEADERS_DIRECTORY = ./engine/includes/
ENGINE_HEADERS_LIST = engine.h
ENGINE_HEADERS = $(addprefix $(ENGINE_HEADERS_DIRECTORY), $(ENGINE_HEADERS_LIST))
ENGINE_INCLUDES = -I $(ENGINE_HEADERS_DIRECTORY)

ENGINE_SRCS = $(addprefix $(ENGINE_SRCS_DIRECTORY), $(ENGINE_SRCS_LIST))

ENGINE_OBJS = $(addprefix $(ENGINE_OBJS_DIRECTORY), $(ENGINE_OBJS_LIST))

ENGINE_OBJS_LIST = $(patsubst %.c, %.o, $(ENGINE_SRCS_LIST))

EDITOR_OBJS_DIRECTORY = ./editor/objs/
EDITOR_SRCS_DIRECTORY = ./editor/srcs/
EDITOR_HEADERS_DIRECTORY = ./editor/includes/
EDITOR_HEADERS_LIST = editor.h
EDITOR_SRCS_LIST = 		checksum.c \
						checksum_errors.c
EDITOR_HEADERS = $(addprefix $(EDITOR_HEADERS_DIRECTORY), $(EDITOR_HEADERS_LIST))
EDITOR_INCLUDES = -I$(EDITOR_HEADERS_DIRECTORY)
EDITOR_SRCS = $(addprefix $(EDITOR_SRCS_DIRECTORY), $(EDITOR_SRCS_LIST))
EDITOR_OBJS = $(addprefix $(EDITOR_OBJS_DIRECTORY), $(EDITOR_OBJS_LIST))
EDITOR_OBJS_LIST = $(patsubst %.c, %.o, $(EDITOR_SRCS_LIST))

all: $(NAME)

$(NAME): $(LIBFT) $(ENGINE_OBJS_DIRECTORY) $(ENGINE_OBJS) $(GAME_OBJS_DIRECTORY) $(GAME_OBJS)
	$(CC) -Ofast -O3 -o $(NAME) $(GAME_OBJS) $(ENGINE_OBJS) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $(LIBFT) -L $(SDL_LIB) -lSDL2 -L $(SDL_TTF_LIB) -lSDL2_ttf -L $(SDL_MIXER_LIB) -lSDL2_mixer

$(ENGINE_OBJS_DIRECTORY):
	mkdir -p $(ENGINE_OBJS_DIRECTORY)
	echo "$(NAME): $(ENGINE_OBJS_DIRECTORY) was created"

$(ENGINE_OBJS_DIRECTORY)%.o: $(ENGINE_SRCS_DIRECTORY)%.c $(ENGINE_HEADERS)
	$(CC) -Ofast -O3 $(FLAGS) -c $(ENGINE_INCLUDES) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $< -o $@

$(GAME_OBJS_DIRECTORY):
	mkdir -p $(GAME_OBJS_DIRECTORY)
	echo "$(NAME): $(GAME_OBJS_DIRECTORY) was created"

$(GAME_OBJS_DIRECTORY)%.o: $(GAME_SRCS_DIRECTORY)%.c $(GAME_HEADERS)
	$(CC) -Ofast -O3 $(FLAGS) -c $(GAME_INCLUDES) -I $(ENGINE_HEADERS_DIRECTORY) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $< -o $@
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

crc: $(LIBFT) $(ENGINE_OBJS_DIRECTORY) $(ENGINE_OBJS) $(EDITOR_OBJS_DIRECTORY) $(EDITOR_OBJS)
	$(CC) -o $(CRC) $(ENGINE_OBJS) $(EDITOR_OBJS) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $(LIBFT) -L $(SDL_LIB) -lSDL2 -L $(SDL_TTF_LIB) -lSDL2_ttf -L $(SDL_MIXER_LIB) -lSDL2_mixer

$(EDITOR_OBJS_DIRECTORY):
	mkdir -p $(EDITOR_OBJS_DIRECTORY)
	echo "$(NAME): $(EDITOR_OBJS_DIRECTORY) was created"

$(EDITOR_OBJS_DIRECTORY)%.o: $(EDITOR_SRCS_DIRECTORY)%.c $(EDITOR_HEADERS)
	$(CC) $(FLAGS) -c $(EDITOR_INCLUDES) -I $(EDITOR_HEADERS_DIRECTORY) -I $(LIBFT_DIRECTORY_HEADERS) -I $(ENGINE_HEADERS_DIRECTORY) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $< -o $@
