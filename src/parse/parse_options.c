/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <israel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:07 by yunlovex          #+#    #+#             */
/*   Updated: 2025/01/04 17:32:53 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_textures(char *line, mlx_texture_t *walls[5])
{
	char	**path;

	path = ft_split(line, ' ');
	if (!path)
		cub3d_error("malloc", 1);
	if (!path[0] || !path[1])
		cub3d_error("Invalid texture path", 1);
	if (path[2])
		cub3d_error("Too many texture arguments", 1);
	if (ft_strnstr(line, "NO", 2) == line && !walls[0])
		walls[0] = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "SO", 2) == line && !walls[2])
		walls[2] = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "EA", 2) == line && !walls[1])
		walls[1] = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "WE", 2) == line && !walls[3])
		walls[3] = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "HN", 2) == line && !walls[4])
		walls[4] = mlx_load_png(path[1]);
	else
	{
		printf("line: %s\n", line);
		cub3d_error("Invalid texture", 1);
	}
	double_free(path);
	free(line);
	return (1);
}

static int	parse_colors(char *line, t_colors *colors)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		cub3d_error("malloc", 1);
	if (!split[1])
		cub3d_error("Invalid color", 1);
	rgb = ft_split(split[1], ',');
	if (!rgb)
		cub3d_error("malloc", 1);
	if (*line == 'F' && rgb[0] && rgb[1] && rgb[2])
		colors->floor_color = color_rgba(ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	else if (*line == 'C' && rgb[0] && rgb[1] && rgb[2])
		colors->ceiling_color = color_rgba(ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	else
		cub3d_error("Invalid color", 1);
	double_free(rgb);
	double_free(split);
	return (1);
}

int parse_options(char *line, t_cub3d *cub3d)
{
    char    *tmp;
    int     ret;

    tmp = ft_strtrim(line, " \n");
    if (!tmp)
        cub3d_error("malloc", 1);
        
    ret = 0;
    if (ft_strnstr(tmp, "NO", 2) == tmp || ft_strnstr(tmp, "SO", 2) == tmp
        || ft_strnstr(tmp, "EA", 2) == tmp || ft_strnstr(tmp, "WE", 2) == tmp
        || ft_strnstr(tmp, "HN", 2) == tmp)
        ret = parse_textures(tmp, cub3d->textures);
    else if (*tmp == 'F' || *tmp == 'C')
        ret = parse_colors(tmp, &cub3d->colors);
    else
        free(tmp);  // Free tmp if not handled by parse_textures or parse_colors
        
    free(line);  // Free the original line
    return ret;
}
