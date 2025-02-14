/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:50:12 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/14 08:41:42 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strchr(line, '1') || ft_strchr(line, '2')
			|| ft_strchr(line, 'N') || ft_strchr(line, 'S')
			|| ft_strchr(line, 'E') || ft_strchr(line, 'W')
			|| ft_strchr(line, '0') || ft_strchr(line, 'D'))
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
int	check_line(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] != '\t'
			&& line[x] != ' ' && line[x] != '0'
			&& line[x] != '1' && line[x] != '2'
			&& line[x] != 'N' && line[x] != 'S'
			&& line[x] != 'E' && line[x] != 'W'
			&& line[x] != 'D')
			return (EXIT_FAILURE);
		x++;
	}
	if (!x)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	check_cell(char **grid, int y, int x, int height)
{
	size_t	width;

	if (y < 0 || y >= height || !grid[y])
		return ;
	width = ft_strlen(grid[y]);
	if (x < 0 || x >= (int) width)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'm' || grid[y][x] == ' ')
		return ;
	if (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S'
		&& grid[y][x] != 'E' && grid[y][x] != 'W' && grid[y][x] != 'D')
		return ;
	if (y == 0 || y == height - 1 || x == 0 || x == (int)width - 1)
		return ;
	if (!grid[y + 1] || !grid[y - 1]
		|| x >= (int) ft_strlen(grid[y + 1])
		|| x >= (int) ft_strlen(grid[y - 1])
		|| grid[y + 1][x] == ' ' || grid[y - 1][x] == ' '
		|| grid[y][x + 1] == ' ' || grid[y][x - 1] == ' ')
		return ;
	grid[y][x] = 'm';
	check_cell(grid, y - 1, x, height);
	check_cell(grid, y + 1, x, height);
	check_cell(grid, y, x - 1, height);
	check_cell(grid, y, x + 1, height);
}

void	find_zero(char **grid, int *y, int *x, int rows)
{
	size_t	width;

	*y = 0;
	while (*y < rows && grid[*y])
	{
		*x = 0;
		width = ft_strlen(grid[*y]);
		while (*x < (int)width)
		{
			if (grid[*y][*x] == '0')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

int	check_map(char **grid, int rows)
{
	char	**copy_grid;
	int		y;
	int		x;
	int		ret;

	if (!grid || rows <= 0)
		return (EXIT_FAILURE);
	copy_grid = ft_dstrdup(grid, rows);
	if (!copy_grid)
		return (EXIT_FAILURE);
	y = 0;
	x = 0;
	find_zero(copy_grid, &y, &x, rows);
	if (y < rows && x < (int)ft_strlen(copy_grid[y]))
		check_cell(copy_grid, y, x, rows);
	find_zero(copy_grid, &y, &x, rows);
	if (y >= rows)
		ret = EXIT_SUCCESS;
	else
		ret = EXIT_FAILURE;
	if (copy_grid)
		double_free(copy_grid);
	return (ret);
}
