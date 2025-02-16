/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapParser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:19:43 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/16 17:12:04 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (check_map(map->grid, map->height));
}
