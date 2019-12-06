/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:59:27 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 20:54:06 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <SDL.h>
# include <SDL_ttf.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

# define SIZE_WIN_X 2048
# define SIZE_WIN_Y 1152
# define POINT_SIZE 10
# define STEP 50
# define GRID_SIZE 600
# define GRID_SIZE_X 30
# define GRID_SIZE_Y 20
# define XO 0
# define YO 0
# define X1 SIZE_WIN_X - 1

# define CODE_ALREADY_EXIST -1
# define CODE_OK 0
# define CODE_NO_FILENAME -2
# define CODE_NO_PLAYER -3
# define CODE_OVERLAY_OR_DOUBLEPORT -4

# define COLOR_UNPUSHED 0
# define COLOR_PUSHED 1
# define SAVE_BUTTON 2

# define WALL_TYPE 1
# define PLAYER_TYPE 2
# define SPRITE_TYPE 3

# define PLAYER_PUSH 0
# define MEDKIT_PUSH 1
# define ARMOR_PUSH 2
# define POWER_UP_PUSH 3
# define RIFLE_AMMO_PUSH 4
# define PLASMA_GUN_PUSH 5
# define PLASMA_AMMO_PUSH 6
# define BARREL_PUSH 7
# define AFRIT_PUSH 8
# define CACODEMON_PUSH 9
# define IMP_PUSH 10
# define JETPACK_PUSH 11
# define WALL_PUSH 12
# define SAVE_PUSH 13

# define BUTTON_PLAYER_X1 SIZE_WIN_X * 0.8 + SIZE_WIN_X * 0.2 * 0.1
# define BUTTON_PLAYER_Y1 SIZE_WIN_Y * 0.1 * 0.55
# define BUTTON_PLAYER_X2 BUTTON_PLAYER_X1 + SIZE_WIN_X * 0.2 * 0.6
# define BUTTON_PLAYER_Y2 BUTTON_PLAYER_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_MEDKIT_X1 BUTTON_PLAYER_X1
# define BUTTON_MEDKIT_Y1 BUTTON_PLAYER_Y1 * 2
# define BUTTON_MEDKIT_X2 BUTTON_PLAYER_X2
# define BUTTON_MEDKIT_Y2 BUTTON_MEDKIT_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_ARMOR_X1 BUTTON_PLAYER_X1
# define BUTTON_ARMOR_Y1 BUTTON_PLAYER_Y1 * 3
# define BUTTON_ARMOR_X2 BUTTON_PLAYER_X2
# define BUTTON_ARMOR_Y2 BUTTON_ARMOR_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_POWER_UP_X1 BUTTON_PLAYER_X1
# define BUTTON_POWER_UP_Y1 BUTTON_PLAYER_Y1 * 4
# define BUTTON_POWER_UP_X2 BUTTON_PLAYER_X2
# define BUTTON_POWER_UP_Y2 BUTTON_POWER_UP_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_RIFLE_AMMO_X1 BUTTON_PLAYER_X1
# define BUTTON_RIFLE_AMMO_Y1 BUTTON_PLAYER_Y1 * 5
# define BUTTON_RIFLE_AMMO_X2 BUTTON_PLAYER_X2
# define BUTTON_RIFLE_AMMO_Y2 BUTTON_RIFLE_AMMO_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_PLASMA_GUN_X1 BUTTON_PLAYER_X1
# define BUTTON_PLASMA_GUN_Y1 BUTTON_PLAYER_Y1 * 6
# define BUTTON_PLASMA_GUN_X2 BUTTON_PLAYER_X2
# define BUTTON_PLASMA_GUN_Y2 BUTTON_PLASMA_GUN_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_PLASMA_AMMO_X1 BUTTON_PLAYER_X1
# define BUTTON_PLASMA_AMMO_Y1 BUTTON_PLAYER_Y1 * 7
# define BUTTON_PLASMA_AMMO_X2 BUTTON_PLAYER_X2
# define BUTTON_PLASMA_AMMO_Y2 BUTTON_PLASMA_AMMO_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_BARREL_X1 BUTTON_PLAYER_X1
# define BUTTON_BARREL_Y1 BUTTON_PLAYER_Y1 * 8
# define BUTTON_BARREL_X2 BUTTON_PLAYER_X2
# define BUTTON_BARREL_Y2 BUTTON_BARREL_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_AFRIT_X1 BUTTON_PLAYER_X1
# define BUTTON_AFRIT_Y1 BUTTON_PLAYER_Y1 * 9
# define BUTTON_AFRIT_X2 BUTTON_PLAYER_X2
# define BUTTON_AFRIT_Y2 BUTTON_AFRIT_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_CACODEMON_X1 BUTTON_PLAYER_X1
# define BUTTON_CACODEMON_Y1 BUTTON_PLAYER_Y1 * 10
# define BUTTON_CACODEMON_X2 BUTTON_PLAYER_X2
# define BUTTON_CACODEMON_Y2 BUTTON_CACODEMON_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_IMP_X1 BUTTON_PLAYER_X1
# define BUTTON_IMP_Y1 BUTTON_PLAYER_Y1 * 11
# define BUTTON_IMP_X2 BUTTON_PLAYER_X2
# define BUTTON_IMP_Y2 BUTTON_IMP_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_JETPACK_X1 BUTTON_PLAYER_X1
# define BUTTON_JETPACK_Y1 BUTTON_PLAYER_Y1 * 12
# define BUTTON_JETPACK_X2 BUTTON_PLAYER_X2
# define BUTTON_JETPACK_Y2 BUTTON_JETPACK_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_WALL_X1 BUTTON_PLAYER_X1
# define BUTTON_WALL_Y1 BUTTON_PLAYER_Y1 * 13
# define BUTTON_WALL_X2 BUTTON_PLAYER_X2
# define BUTTON_WALL_Y2 BUTTON_WALL_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_SAVE_X1 BUTTON_PLAYER_X1
# define BUTTON_SAVE_Y1 BUTTON_PLAYER_Y1 * 15
# define BUTTON_SAVE_X2 BUTTON_PLAYER_X2
# define BUTTON_SAVE_Y2 BUTTON_SAVE_Y1 + SIZE_WIN_Y * 0.05

# define BUTTON_STATUS_X1 BUTTON_PLAYER_X1
# define BUTTON_STATUS_Y1 BUTTON_PLAYER_Y1 * 16
# define BUTTON_STATUS_X2 BUTTON_PLAYER_X2
# define BUTTON_STATUS_Y2 BUTTON_STATUS_Y1 + SIZE_WIN_Y * 0.05

# define INPUT_FIELD_X1 BUTTON_PLAYER_X1
# define INPUT_FIELD_Y1 BUTTON_PLAYER_Y1 * 14.5
# define INPUT_FIELD_X2 BUTTON_PLAYER_X2
# define INPUT_FIELD_Y2 INPUT_FIELD_Y1 + SIZE_WIN_Y * 0.03

# define INPUT_MAP_NAME_SIZE_X SIZE_WIN_X * 0.16
# define INPUT_MAP_NAME_Y SIZE_WIN_Y * 0.8
# define INPUT_LETTER_SIZE 17

typedef struct				s_input_field
{
	int						x;
	int						y;
	int						size_x;
	int						size_y;
	int						max_text_size;
	char					*text;
	int						text_size;
}							t_input_field;

typedef struct				s_ed_point
{
	int						x;
	int						y;
}							t_ed_point;

typedef struct				s_walls
{
	int						portal;
	int						wall_id;
	int						x1;
	int						y1;
	int						x2;
	int						y2;
	int						neighbour_x1;
	int						neighbour_y1;
	int						neighbour_x2;
	int						neighbour_y2;
	struct s_walls			*next;
}							t_walls;

typedef struct				s_ed_sector
{
	t_ed_point				point[1000];
	t_walls					walls[1000];
	int						size;
	int						num_of_sector;
	int						type_of_point;
	double					cmn;
	double					rh;
	double					sh;
	int						z;
	int						check;
	int						num_of_walls;
	int						portal_advent;
	int						total_num_of_obj;
	int						local_intersection;
	struct s_ed_sector		*next;
}							t_ed_sector;

typedef struct				s_commands
{
	int						type;
	struct s_commands		*next;
}							t_commands;

typedef struct				s_ed_sprite
{
	int						type;
	int						x;
	int						y;
	int						sector;
	struct s_ed_sprite		*next;
}							t_ed_sprite;

typedef struct				s_sdl
{
	SDL_Window				*window;
	SDL_Renderer			*renderer;
	SDL_Surface				*surface;
	SDL_Event				window_event;
	SDL_Point				mouse_position;
	TTF_Font				*font;
	SDL_Texture				*text;
	int						sect_count;
	int						command_count;
	int						button_pushed;
	int						type_pressed;
	int						count;
	int						num;
	int						sprite_in_sector;
	int						status_code;
	int						is_input;
	int						is_overlay;
	int						is_doubleport;
	int						id;
	int						save_click;
	char					*char_id;
	struct s_ed_point		grid_field[GRID_SIZE];
	struct s_ed_sector		*sectors;
	struct s_commands		*commands;
	struct s_ed_point		*player;
	struct s_ed_sprite		*sprites;
	struct s_input_field	*map_name;
}							t_sdl;

void						init_sdl(t_sdl *sdl);
void						init_grid(t_ed_point *grid_field);
t_ed_sector					*init_sector();
t_walls						*init_wall(void);
void						init_player(t_sdl *sdl);
t_ed_sprite					*init_sprite();
void						big_loop(t_sdl *sdl);
void						text_events(t_sdl *sdl);
void						textinput(t_sdl *sdl);
void						exit_events(t_sdl *sdl);
void						clicks3(t_sdl *sdl);
void						input_field_click(t_sdl *sdl);
void						delete_one_symbol(t_sdl *sdl);
void						save_the_grid(t_ed_point *grid_field,
							SDL_Rect grid);
void						add_point(t_sdl *sdl, t_ed_sector *sector, int i);
void						make_wall(t_sdl *sdl);
void						save_wall(t_ed_sector *sector, int i);
void						which_of_points(t_sdl *sdl, t_ed_sector *sector,
											t_walls *walls, int i);
void						cut_the_rope(t_sdl *sdl, t_ed_sector *sector,
							int i);
int							check_the_grid(t_ed_point *grid_field, int x,
							int y);
void						redraw(t_sdl *sdl);
void						draw_sidebar(t_sdl *sdl);
void						player_button(t_sdl *sdl, SDL_Rect *button);
void						medkit_button(t_sdl *sdl, SDL_Rect *button);
void						armor_button(t_sdl *sdl, SDL_Rect *button);
void						power_up_button(t_sdl *sdl, SDL_Rect *button);
void						rifle_ammo_button(t_sdl *sdl, SDL_Rect *button);
void						plasma_gun_button(t_sdl *sdl, SDL_Rect *button);
void						plasma_ammo_button(t_sdl *sdl, SDL_Rect *button);
void						barrel_button(t_sdl *sdl, SDL_Rect *button);
void						afrit_button(t_sdl *sdl, SDL_Rect *button);
void						cacodemon_button(t_sdl *sdl, SDL_Rect *button);
void						imp_button(t_sdl *sdl, SDL_Rect *button);
void						jetpack_button(t_sdl *sdl, SDL_Rect *button);
void						wall_button(t_sdl *sdl, SDL_Rect *button);
void						input_field(t_sdl *sdl);
void						save_button(t_sdl *sdl, SDL_Rect *button);
void						status_text(t_sdl *sdl, SDL_Rect *button);
void						draw_button(t_sdl *sdl, SDL_Rect button, char *text,
										int color);
void						draw_headline(t_sdl *sdl);
void						draw_text(t_sdl *sdl, char *text, SDL_Rect button,
										SDL_Color color);
void						draw_grid(t_sdl *sdl);
void						draw(t_sdl *sdl);
void						status_text(t_sdl *sdl, SDL_Rect *button);
void						choose_sprite_color(t_sdl *sdl,
							t_ed_sprite *sprites);
void						draw_a_sector(t_sdl *sdl, t_ed_sector *sector,
							int i);
void						draw_a_point(t_sdl *sdl, t_ed_point *point, int i);
void						delete_player(t_ed_point *player);
void						reset(t_sdl *sdl);
void						delete_last_command(t_sdl *sdl);
void						delete_point(t_ed_sector *sector);
void						remove_last_sprite(t_ed_sprite **sprites);
void						remove_last_point(t_sdl *sdl, t_ed_sector **head);
void						add_command(t_sdl *sdl, t_commands **commands,
										int type);
t_ed_sector					*get_last_sector(t_ed_sector *head);
t_ed_sprite					*find_last_sprite(t_ed_sprite *sprites);
SDL_Color					*create_sdl_color(int r, int g, int b, int a);
SDL_Rect					*create_rect(int x, int y, int w, int h);
char						*cut_the_end(char *text);
void						choose_type_of_point(t_ed_sector **stuffbox,
							int type);
void						make_player_or_sprite(t_sdl *sdl);
int							check_intersect_l(t_sdl *sdl, t_ed_sector *head,
												int x2, int y2);
int							check_intersect_r(t_sdl *sdl, t_ed_sector *head,
												int x2, int y2);
int							count_intersection(t_sdl *sdl, t_ed_sector *head,
												int count);
void						find_portals(t_sdl *sdl);
int							check_point(t_ed_sector *head, int num_of_sector,
										int x, int y);
int							check_overlays(t_sdl *sdl);
int							check_doubleport(t_sdl *sdl);
void						set_sprite(t_sdl *sdl, int x, int y);
int							bigscarycondition(t_sdl *sdl);
void						save_click(t_sdl *sdl);
int							save_map(t_sdl *sdl, char *map_name);
void						write_world(t_sdl *sdl, int fd);
int							get_sector_count(t_ed_sector *sect);
int							write_vertexes_wall(t_sdl *sdl, int fd);
void						write_polygone(t_sdl *sdl, int fd);
void						write_player(t_sdl *sdl, int fd);
void						write_vertexes_sprite(t_sdl *sdl, int fd,
													int last_id);
void						write_sprites(t_sdl *sdl, int fd, int last_id);
void						write_sectors(t_sdl *sdl, int fd);
void						write_objects(t_sdl *sdl, int fd);
void						write_to_file(int fd, char *data, int numdata);
int							is_clockwise(t_walls *wall);
int							check_local_intersection(t_sdl *sdl,
										t_ed_sector *cur_sect, t_walls *wall);
int							check_sect_intersects(t_sdl *sdl,
										int num_of_sector, int x, int y);

t_sdl						*init_editor(void);
void						run_editor(t_sdl *sdl);
void						stop_editor(t_sdl *sdl);
#endif
