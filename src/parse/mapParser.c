/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapParser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:19:43 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/14 09:33:41 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize_door_states(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		map->door_states[y] = ft_calloc(map->width, sizeof(int));
		x = 0;
		while (map->grid[y][x] != '\0')
		{
			if (map->grid[y][x] == 'D')
				map->door_states[y][x] = 1;
			else
				map->door_states[y][x] = -1;
			x++;
		}
		y++;
	}
}

static void	read_map_lines(int fd, t_map *map)
{
	char	*line;
	char	*tmp;
	int		y;

	y = 0;
	line = skip_empty_lines(fd);
	while (line)
	{
		tmp = ft_strtrim(line, "\n");
		free(line);
		if (check_line(tmp))
			return (free(tmp));
		map->grid = ft_realloc(map->grid, sizeof(char *) * y,
				sizeof(char *) * (y + 1));
		if (!map->grid)
			return (free(tmp));
		map->grid[y++] = tmp;
		if ((int) ft_strlen(tmp) > map->width)
			map->width = ft_strlen(tmp);
		line = get_next_line(fd);
	}
	free(line);
	map->height = y;
}

int	parse_map(int fd, t_map *map)
{
	read_map_lines(fd, map);
	map->door_states = ft_calloc(map->height * map->width, sizeof(int *));
	initialize_door_states(map);
	return (check_map(map->grid, map->height));
}
