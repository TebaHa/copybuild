# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 21:35:31 by zytrams           #+#    #+#              #
#    Updated: 2019/11/03 13:49:09 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom_nukem

CC = gcc

FLAGS_FAST = -Ofast -march=native -m64 -O2 -flto -funroll-loops
FLAGS_42 = -Wall -Wextra -Werror
FLAGS = $(FLAGS_FAST)

ID_UN := $(shell id -un)

ifeq ($(ID_UN), tyanyahiao)
	CELLAR_FOLDER = /usr/local/Cellar/
else
	CELLAR_FOLDER = /Users/$(ID_UN)/.brew/Cellar/
endif

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./lib/libft/
LIBFT_DIRECTORY_HEADERS = $(LIBFT_DIRECTORY)includes

GAME_SRCS_LIST =	freefps.c \
					game_controller_down.c \
					game_controller_up.c \
					game_movement_funs.c \
					game_movement.c \
					game_collision_detector.c \
					gravitation.c \
					multi_threading.c \
					weapon_fire.c \

SDL = $(SDL_DIRECTORY)libmlx.a
SDL_DIRECTORY = ./lib/sdl2/
SDL_INCLUDES_DIRECTORY = ./engine/includes/SDL2/

SDL_FOLDER = $(CELLAR_FOLDER)sdl2/2.0.10/include/SDL2
SDL_LIB = $(CELLAR_FOLDER)sdl2/2.0.10/lib

SDL_TTF_FOLDER = $(CELLAR_FOLDER)sdl2_ttf/2.0.15/include/SDL2
SDL_TTF_LIB = $(CELLAR_FOLDER)sdl2_ttf/2.0.15/lib

SDL_MIXER_FOLDER = $(CELLAR_FOLDER)sdl2_mixer/2.0.4/include/SDL2
SDL_MIXER_LIB = $(CELLAR_FOLDER)sdl2_mixer/2.0.4/lib

GAME_OBJS_DIRECTORY = ./game/objs/
GAME_SRCS_DIRECTORY = ./game/srcs/

GAME_HEADERS_DIRECTORY = ./game/includes/
GAME_HEADERS_LIST = game.h
GAME_HEADERS = $(addprefix $(GAME_HEADERS_DIRECTORY), $(GAME_HEADERS_LIST))
GAME_INCLUDES = -I$(GAME_HEADERS_DIRECTORY)

GAME_SRCS = $(addprefix $(GAME_SRCS_DIRECTORY), $(GAME_SRCS_LIST))

GAME_OBJS = $(addprefix $(GAME_OBJS_DIRECTORY), $(GAME_OBJS_LIST))

GAME_OBJS_LIST = $(patsubst %.c, %.o, $(GAME_SRCS_LIST))

ENGINE_SRCS_LIST =	$(PARSER_SRCS_LIST) \
					line_bresenham.c \
					line_bresenham2.c \
					checksum.c \
					engine_close.c \
					line_color.c \
					engine_main.c \
					error_handler.c \
					engine_font.c \
					hud_draw.c \
					hud_draw1.c \
					loader_images.c \
					intersection_funs_help.c \
					intersection_funs.c \
					vectors_normal.c \
					objects_help.c \
					objects.c \
					game_pickup.c \
					relative_coord.c \
					render_cycle.c \
					render_cycle2.c \
					render_main.c \
					render_particle_2.c \
					render_particle.c \
					render_stack.c \
					render_wall_help.c \
					render_wall.c \
					render_wall2.c \
					render_world.c \
					render_background.c \
					sprite_data.c \
					shoot_help.c \
					shoot_main.c \
					shoot_main2.c \
					sort.c \
					sound_2.c \
					sound.c \
					sprite_render_2.c \
					sprite_render_stack.c \
					sprite_render.c \
					engine_texture_math.c \
					engine_texture.c \
					utility.c \
					utils_check_stack.c \

PARSER_SRCS_LIST =	parser_button.c \
					parser_color.c \
					parser_enemy.c \
					parser_errors_2.c \
					parser_errors_3.c \
					parser_errors.c \
					parser_filler.c \
					parser_hud.c \
					parser_filename.c \
					parser_items_2.c \
					parser_items.c \
					parser_object.c \
					parser_package.c \
					parser_player_2.c \
					parser_player.c \
					parser_point_3d.c \
					parser_polygone.c \
					parser_reader.c \
					parser_sector_2.c \
					parser_sector.c \
					parser_sprite_2.c \
					parser_sprite.c \
					parser_sprite_360.c \
					parser_sprobject.c \
					parser_texture.c \
					parser_utility.c \
					parser_weapon.c \
					parser_world.c \
					parser_worldbox.c \
					parser.c \
					parser_wallobjects.c \

ENGINE_OBJS_DIRECTORY = ./engine/objs/
ENGINE_SRCS_DIRECTORY = ./engine/srcs/

ENGINE_HEADERS_DIRECTORY = ./engine/includes/
ENGINE_HEADERS_LIST = engine.h
ENGINE_HEADERS = $(addprefix $(ENGINE_HEADERS_DIRECTORY), $(ENGINE_HEADERS_LIST))
ENGINE_INCLUDES = -I $(ENGINE_HEADERS_DIRECTORY)

SDL_INCLUDES = -I $(SDL_INCLUDES_DIRECTORY)

ENGINE_SRCS = $(addprefix $(ENGINE_SRCS_DIRECTORY), $(ENGINE_SRCS_LIST))

ENGINE_OBJS = $(addprefix $(ENGINE_OBJS_DIRECTORY), $(ENGINE_OBJS_LIST))

ENGINE_OBJS_LIST = $(patsubst %.c, %.o, $(ENGINE_SRCS_LIST))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(ENGINE_OBJS_DIRECTORY) $(ENGINE_OBJS) $(GAME_OBJS_DIRECTORY) $(GAME_OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(GAME_OBJS) $(ENGINE_OBJS) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) $(SDL_INCLUDES) -I $(SDL_MIXER_FOLDER) $(LIBFT) -L $(SDL_LIB) -lSDL2 -L $(SDL_TTF_LIB) -lSDL2_ttf -L $(SDL_MIXER_LIB) -lSDL2_mixer
	@echo "\n$(GREEN)DoomNukem created$(RESET)"

$(ENGINE_OBJS_DIRECTORY):
	@mkdir -p $(ENGINE_OBJS_DIRECTORY)
	@echo "$(NAME): $(ENGINE_OBJS_DIRECTORY) was created"

$(ENGINE_OBJS_DIRECTORY)%.o: $(ENGINE_SRCS_DIRECTORY)%.c $(ENGINE_HEADERS)
	@$(CC) $(FLAGS) -c $(ENGINE_INCLUDES) -I $(LIBFT_DIRECTORY_HEADERS) -I $(SDL_FOLDER) $(SDL_INCLUDES) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $< -o $@
	@echo -n '.'

$(GAME_OBJS_DIRECTORY):
	@mkdir -p $(GAME_OBJS_DIRECTORY)
	@echo "$(NAME): $(GAME_OBJS_DIRECTORY) was created"

$(GAME_OBJS_DIRECTORY)%.o: $(GAME_SRCS_DIRECTORY)%.c $(GAME_HEADERS)
	@$(CC) $(FLAGS) -c $(GAME_INCLUDES) -I $(ENGINE_HEADERS_DIRECTORY) -I $(LIBFT_DIRECTORY_HEADERS) $(SDL_INCLUDES) -I $(SDL_FOLDER) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) $< -o $@
	@echo -n '.'

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@rm -rf $(GAME_OBJS_DIRECTORY)/*.o
	@rm -rf $(ENGINE_OBJS_DIRECTORY)/*.o
	@rm -rf $(EDITOR_OBJS_DIRECTORY)/*.o
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@echo "$(RED)Objs deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(EDITOR)
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@echo "$(RED)DoomNukem deleted$(RESET)"

re: fclean all

le_clean:
	@rm -rf $(GAME_OBJS_DIRECTORY)/*.o
	@rm -rf $(ENGINE_OBJS_DIRECTORY)/*.o
	@rm -rf $(EDITOR_OBJS_DIRECTORY)/*.o
	@echo "$(RED)Objs deleted (excluding libft)$(RESET)"
	@rm -rf $(NAME)
	@rm -rf $(EDITOR)
	@echo "$(RED)DoomNukem deleted (excluding libft.a)$(RESET)"

le: le_clean all

id:
	echo $(ID_UN)
