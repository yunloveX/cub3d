/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:19:43 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 13:10:01 by yunlovex         ###   ########.fr       */
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
			|| ft_strchr(line, 'E') || ft_strchr(line, 'W')
			|| ft_strchr(line, '0'))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/**
 * Hay que poner los valores aceptados en el enunciado
 * 			0 1 2 N S E W
 * mas los que queramos usar nosotros
 */
static int	check_line(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] != '\t'
			&& line[x] != ' ' && line[x] != '0'
			&& line[x] != '1' && line[x] != '2'
			&& line[x] != 'N' && line[x] != 'S'
			&& line[x] != 'E' && line[x] != 'W')
			return (EXIT_FAILURE);
		x++;
	}
	if (!x)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	check_cell(char **grid, int y, int x, int height)
{
	int	width;

	width = ft_strlen(grid[y]);
	if ((y <= 0 || x <= 0 || y >= height - 1 || x >= width - 1
		|| !grid[y + 1] || grid[y][x + 1] == '\0'
		|| grid[y][x + 1] == ' ' || grid[y][x - 1] == ' '
		|| grid[y + 1][x] == ' ' || grid[y - 1][x] == ' ')
		|| (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S'
		&& grid[y][x] != 'E' && grid[y][x] != 'W'))
		return ;
	grid[y][x] = 'm';
	check_cell(grid, y - 1, x, height);
	check_cell(grid, y + 1, x, height);
	check_cell(grid, y, x - 1, height);
	check_cell(grid, y, x + 1, height);
}

static void	find_zero(char **grid, int *y, int *x, int rows)
{
	*y = -1;
	while (++*y < rows && grid[*y][*x] != '0')
	{
		*x = 0;
		while (grid[*y][*x])
			if (grid[*y][(*x)++] == '0')
				return ;
	}
	return ;
}

int	check_map(char **grid, int rows)
{
	char	**copy_grid;
	int		y;
	int		x;

	copy_grid = ft_dstrdup(grid, rows);
	y = 0;
	x = 0;
	find_zero(copy_grid, &y, &x, rows);
	check_cell(copy_grid, y, x, rows);
	find_zero(copy_grid, &y, &x, rows);
	double_free(copy_grid);
	if (y < rows)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_map(int fd, t_map *map)
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
			cub3d_error("Invalid map", 1);
		map->grid = ft_realloc(map->grid, sizeof(char *) * y,
				sizeof(char *) * (y + 1));
		if (!map->grid)
			cub3d_error("malloc", 1);
		map->grid[y++] = tmp;
		if ((int) ft_strlen(tmp) > map->width) // y si la línea termina en espacio?
			map->width = ft_strlen(tmp);
		line = get_next_line(fd);
	}
	free(line);
	map->height = y;
	return (check_map(map->grid, map->height));
}
