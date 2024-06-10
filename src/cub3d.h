/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:27:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/10 19:15:12 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "gun.h"
# include "math/mat4.h"
# include "math/v2i.h"
# include "math/v3.h"
# include "network/net.h"
# include "render/font.h"
# include "render/render.h"
# include "render/types.h"
# include "scene.h"

# define YELLOW	"\033[0;33m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define RED	"\033[0;31m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define BLACK	"\033[0;30"
# define WHITE	"\033[0;37m"
# define RESET "\033[0m"

# define EPSILON 1e-1

# include <stdbool.h>

# ifdef _USE_RENDER_THREAD
#  include <pthread.h>
# endif

typedef struct s_map	t_map;

typedef struct s_scoreboard_entry
{
	char	username[MAX_CLIENT_NAME];
	int		present;
	int		kills;
	int		death;
}	t_scoreboard_entry;

typedef struct s_scoreboard
{
	t_scoreboard_entry	entries[MAX_CLIENT + 1];
}	t_scoreboard;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_r3d			*r3d;
	suseconds_t		last_update;

	t_scene			*scene;
	int				entity_id;
	t_map			*map;

	t_panel			*panel;
	t_font			*font;

	bool			*keys;
	bool			buttons[8];

	bool			is_server;
	t_client		client;
	t_server		server;

	float			delta_sec;
	t_v2i			mouse_pos;

	bool			is_focused;

	t_scoreboard	scoreboard;
	t_minimap		minimap;

	t_gun			shotgun;

	t_sprite		player_sprite;
}	t_vars;

inline int	next_entity_id(t_vars *vars)
{
	return (vars->entity_id++);
}

suseconds_t	getms(void);

int	key_pressed_hook(int keycode, t_vars *vars);
int	key_released_hook(int keycode, t_vars *vars);
int	mouse_move_hook(int x, int y, t_vars *vars);
int	mouse_button_pressed_hook(int btn, int _i1, int _i2, t_vars *vars);
int	mouse_button_released_hook(int btn, int _i1, int _i2, t_vars *vars);

#define WALL_SIZE 1.0

enum e_tile
{
	TILE_EMPTY,
	TILE_FULL
};

typedef struct s_map
{
	int			width;
	int			height;

	t_color		floor_color;
	t_color		ceiling_color;

	t_image		*no;
	t_image		*so;
	t_image		*we;
	t_image		*ea;

	int			*tiles;
	t_transform	spawns[MAX_CLIENT];
	int			spawn_count;
	char		**maps;
}	t_map;

typedef struct s_box
{
	t_v3 min;
	t_v3 max;
}	t_box;

t_image	**load_images(int num, ...);

void	map_to_tiles(t_map *map, char **maps, t_scene *scene, t_vars *vars);
void	draw_map(t_r3d *r3d, t_map *map);

char	*read_to_string(char *filename, size_t *len);
char	**create_map(char **cub_file, t_map *map);
bool	is_map_surrounded(char **maps, t_map *map);
char	**fill_map_with_space(char **map, size_t width, size_t height);
bool	find_player_pos(char **maps, t_map *map);
int		calc_map_height(char **maps);
int		calc_map_max_width(char **maps);
bool	fill_texture(t_map *map, char **maps);
char	**create_textures(char **map);
char	*detect_texture_path(char *path);
t_image	*load_texture(char *textures, char *identifier);
char	*detect_identifier(char *texture);
bool 	is_valid_identifier_text(char *str);
bool 	create_material(char *identifier, t_map *map, t_image	*image);
bool 	check_all_materials(t_map *map);
bool	is_valid_identifier_color(char *str);
bool	is_valid_rgb(char **colors, t_map *map);
char	**create_colors(char **map);

void	adjust_player_pos(t_player *player, t_map *map, float delta, t_entity **entities);
bool	collide_point_vs_aabb(t_v3 point, t_box b);
bool	is_valid_file_name(char *str);
bool	is_valid_char_in_map(char **maps, t_map *map);
void	putstr_sep(char *str, char n);
t_box	box_from_entity(t_entity *entity);
bool	is_rgb_range(char *s);
char	**create_colors(char **map);
int		ft_nblen(int nb);
void	fill_color(char *identifier, t_map *map, unsigned char color, int i);
t_entity	*raycast_entity(t_scene *scene, t_transform ray, float size, uint32_t entity_type);

#endif
