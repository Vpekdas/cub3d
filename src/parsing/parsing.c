/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:55:44 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/23 13:36:22 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static bool	is_map_config_valid(t_vars *vars, char **mp_conf, t_alloc_table *at)
{
	if (!is_valid_char_in_map(vars->map.maps, &vars->map))
		return (false);
	if (!is_map_surrounded(vars->map.maps, &vars->map))
		return (false);
	if (!find_player_pos(vars->map.maps, &vars->map))
		return (false);
	if (!fill_texture(&vars->map, mp_conf, at))
		return (false);
	if (!is_valid_rgb(&vars->map, mp_conf, at))
		return (false);
	if (!map_to_tiles(&vars->map, vars->map.maps, vars, at))
		return (false);
	return (true);
}

bool	parsing(t_vars *vars, char **argv, t_alloc_table *at)
{
	char	*line;
	char	**map;

	line = read_to_string(argv[1], NULL, at);
	if (!line)
		return (false);
	if (!map_init(&vars->map))
		return (false); 
	vars->map.map_config = ft_split(line, '\n');
	if (!vars->map.map_config)
		return (false);
	if (!check_enough_line(vars->map.map_config))
		return (false);
	map = create_map(vars->map.map_config, &vars->map, at);
	if (!map)
		return (false);
	vars->map.maps = map_space(map, vars->map.width, vars->map.height, at);
	if (!vars->map.maps)
		return (false);
	if (!is_map_config_valid(vars, vars->map.map_config, at))
		return (false);
	return (true);
}
