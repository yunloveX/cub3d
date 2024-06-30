/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:19:43 by yunlovex          #+#    #+#             */
/*   Updated: 2024/06/30 16:26:28 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strchr(line, '1') || ft_strchr(line, '2')
			|| ft_strchr(line, 'N') || ft_strchr(line, 'S')
			|| ft_strchr(line, 'W') || ft_strchr(line, 'E')
			|| ft_strchr(line, '0'))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/**
 * Hay que poner los valores aceptados en el enunciado
 * 			0 1 2 N S W E
 * mas los que queramos usar nosotros
 */
static int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1'
			&& line[i] != '0' && line[i] != '2'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E')
			return (1);
		i++;
	}
	return (0);
}

static void	check_cell(char **grid, int x, int y)
{
	if (((x == 0 || y == 0 || !grid[x + 1]
				|| grid[x][y + 1] == '\0' || grid[x][y + 1] == ' '
		|| grid[x + 1][y] == ' ')
		&& (grid[x][y] == '0' || grid[x][y] == 'N' || grid[x][y] == 'S'
			|| grid[x][y] == 'W' || grid[x][y] == 'E'))
			|| (grid[x][y] != '0' && grid[x][y] != 'N' && grid[x][y] != 'S'
			&& grid[x][y] != 'W' && grid[x][y] != 'E'))
		return ;
	grid[x][y] = 'm';
	check_cell(grid, x - 1, y);
	check_cell(grid, x + 1, y);
	check_cell(grid, x, y - 1);
	check_cell(grid, x, y + 1);
}

int	check_map(char **grid, int rows)
{
	char	**copy_grid;
	int		i;
	int		j;

	copy_grid = ft_dstrdup(grid, rows);
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (copy_grid[i][j])
			if (copy_grid[i][j] == '0')
				return ;
	}
	check_cell(copy_grid, i, j);
	i = -1;
	while (i < rows)
	{
		j = -1;
		while (copy_grid[i][j])
			if (copy_grid[i][j] == '0')
				return (EXIT_FAILURE);
	}
	double_free(copy_grid);
	return (EXIT_SUCCESS);
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = skip_empty_lines(fd);
	while (line)
	{
		if (check_line(line))
			error_map("Invalid map", 1);
		map->height++;
		map->grid = ft_realloc(map->grid, sizeof(char *) * i,
				sizeof(char *) * (i + 1));
		map->grid[i++] = line;
		if (ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		line = get_next_line(fd);
	}
	free(line);
	map->height = i;
	check_map(map, map->height);
}
