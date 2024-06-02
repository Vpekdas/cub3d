/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:30 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/02 14:55:37 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_map(char **cub_file, t_map *map)
{
	char	**maps;
	int		i;
	int		j;

	i = 6;
	j = 0;
	map->height = calc_map_height(cub_file);
	maps = ft_calloc(map->height + 1, sizeof(char *));
	while (cub_file[i])
		maps[j++] = cub_file[i++];
	map->width = calc_map_max_width(maps);
	return (maps);
}

char	**fill_map_with_space(char **map, size_t width, size_t height)
{
	char	**new_map;
	size_t	i;

	new_map = NULL;
	new_map = ft_calloc(height + 1, sizeof(char *));
	i = 0;
	while (i < height)
	{
		if (ft_strlen(map[i]) < width)
		{
			new_map[i] = ft_calloc(width + 1, sizeof(char));
			ft_memset(new_map[i], ' ', width);
			ft_memcpy(new_map[i], map[i], ft_strlen(map[i]));
		}
		else
			new_map[i] = ft_strdup(map[i]);
		++i;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	map_to_tiles(t_map *map, char **maps)
{
	int		i;
	int		j;
	int		tile_index;

	i = 0;
	tile_index = 0;
	map->tiles = ft_calloc(map->width * map->height, sizeof(int));
	while (maps[i])
	{
		j = 0;
		while (maps[i][j])
		{
			if (maps[i][j] != '1')
				map->tiles[tile_index] = TILE_EMPTY;
			else
				map->tiles[tile_index] = TILE_FULL;
			++tile_index;
			++j;
		}
		++i;
	}
}
