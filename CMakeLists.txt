cmake_minimum_required(VERSION 3.13)
project(DoomNukem)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

include_directories(engine/includes)
include_directories(engine/includes/SDL2)
include_directories(game/includes)
include_directories(lib/libft/includes)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2 REQUIRED)

set(GAME_INC game/includes/game.h)

set(ENG_INC engine/includes/engine.h )

set(GAME_SRC game/srcs/freefps.c
			game/srcs/weapon_fire.c)

set(ENG_SRC engine/srcs/bresenham.c
			engine/srcs/color.c
			engine/srcs/draw.c
			engine/srcs/engine.c
			engine/srcs/error_handler.c
			engine/srcs/hud_draw.c
			engine/srcs/images.c
			engine/srcs/normal.c
			engine/srcs/objects.c
			engine/srcs/parser.c
			engine/srcs/parser_errors.c
			engine/srcs/parser_filler.c
			engine/srcs/parser_reader.c
			engine/srcs/parser_utility.c
			engine/srcs/parser_utility_find.c
			engine/srcs/rasterizer.c
			engine/srcs/shoot.c
			engine/srcs/texture.c
			engine/srcs/utility.c
			engine/srcs/parser_resources.c
			engine/srcs/parser_weapon.c
			engine/srcs/parser_enemy.c
			engine/srcs/relative_coord.c
			engine/srcs/parser_hud_face.c
			engine/srcs/parser_items.c
			engine/srcs/parser_hud.c
			engine/srcs/animator.c
			engine/srcs/zbuff.c)

set(SDL ${SDL_DIRECTORY}libmlx.a)
set(SDL_DIRECTORY lib/sdl2/)
set(SDL_INCLUDES engine/includes/SDL2/)

set(SDL_TTF_DIRECTORY lib/sdl_ttf)

add_executable(DoomNukem ${GAME_INC} ${GAME_SRC}
				${ENG_INC} ${ENG_SRC}
				${SDL_DIRECTORY} ${SDL_INCLUDES})

add_subdirectory(lib/libft)

target_link_libraries(DoomNukem ${SDL2_LIBRARY} libft)
