/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <israel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:19:43 by yunlovex          #+#    #+#             */
/*   Updated: 2025/01/04 18:00:13 by israel           ###   ########.fr       */
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
			&& line[x] != 'E' && line[x] != 'W'
            && line[x] != 'D')
			return (EXIT_FAILURE);
		x++;
	}
	if (!x)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void check_cell(char **grid, int y, int x, int height)
{
    // First check if y is within bounds and grid[y] exists
    if (y < 0 || y >= height || !grid[y])
        return;
        
    // Then check if x is within bounds of current row
    size_t width = ft_strlen(grid[y]);
    if (x < 0 || x >= (int) width)
        return;
        
    // Check if we're at a wall, visited cell, or invalid cell
    if (grid[y][x] == '1' || grid[y][x] == 'm' || grid[y][x] == ' ')
        return;
        
    // Check if we're at a valid cell type
    if (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S'
        && grid[y][x] != 'E' && grid[y][x] != 'W' && grid[y][x] != 'D')
        return;
        
    // Check boundaries
    if (y == 0 || y == height - 1 || x == 0 || x == (int)width - 1)
        return;
        
    // Check surrounding cells exist and aren't spaces
    if (!grid[y + 1] || !grid[y - 1] ||
        x >= (int) ft_strlen(grid[y + 1]) ||
        x >= (int) ft_strlen(grid[y - 1]) ||
        grid[y + 1][x] == ' ' || grid[y - 1][x] == ' ' ||
        grid[y][x + 1] == ' ' || grid[y][x - 1] == ' ')
        return;

    // Mark as visited
    grid[y][x] = 'm';
    
    // Recursively check adjacent cells
    check_cell(grid, y - 1, x, height);
    check_cell(grid, y + 1, x, height);
    check_cell(grid, y, x - 1, height);
    check_cell(grid, y, x + 1, height);
}

static void find_zero(char **grid, int *y, int *x, int rows)
{
    size_t width;

    *y = 0;
    while (*y < rows && grid[*y])
    {
        *x = 0;
        width = ft_strlen(grid[*y]);
        while (*x < (int)width)
        {
            if (grid[*y][*x] == '0')
                return;
            (*x)++;
        }
        (*y)++;
    }
}

int check_map(char **grid, int rows)
{
    char    **copy_grid;
    int     y;
    int     x;
    int     ret;

    if (!grid || rows <= 0)
        return (EXIT_FAILURE);
        
    copy_grid = ft_dstrdup(grid, rows);
    if (!copy_grid)
        return (EXIT_FAILURE);

    // Find initial zero position
    y = 0;
    x = 0;
    find_zero(copy_grid, &y, &x, rows);
    
    // If we found a zero, flood fill from there
    if (y < rows && x < (int)ft_strlen(copy_grid[y]))
        check_cell(copy_grid, y, x, rows);
        
    // Try to find another zero
    find_zero(copy_grid, &y, &x, rows);
    
    // If we found another zero, map is not enclosed
    ret = (y >= rows) ? EXIT_SUCCESS : EXIT_FAILURE;
    
    // Clean up
    if (copy_grid)
        double_free(copy_grid);
    return (ret);
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
		if ((int) ft_strlen(tmp) > map->width)
			map->width = ft_strlen(tmp);
		line = get_next_line(fd);
	}
	free(line);
	map->height = y;
    map->door_states = ft_calloc(map->height, sizeof(int *));
    y = 0;
    while (y < map->height) {
        map->door_states[y] = ft_calloc(map->width, sizeof(int));
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == 'D') map->door_states[y][x] = 1;
        }
        y++;
    }
	return (check_map(map->grid, map->height));
}
