/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:07 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 08:36:52 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_textures(char *line, t_walls *walls)
{
	char	**path;

	path = ft_split(line, ' ');
	if (!path)
		cub3d_error("malloc", 1);
	if (!path[0] || !path[1])
		cub3d_error("Invalid texture path", 1);
	if (ft_strnstr(line, "NO ", 3) == line && !walls->north)
		walls->north = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "SO ", 3) == line && !walls->south)
		walls->south = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "EA ", 3) == line && !walls->east)
		walls->east = mlx_load_png(path[1]);
	else if (ft_strnstr(line, "WE ", 3) == line && !walls->west)
		walls->west = mlx_load_png(path[1]);
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
		cub3d_error("Invalid color0", 1);
	rgb = ft_split(split[1], ',');
	if (!rgb)
		cub3d_error("malloc", 1);
	if (*line == 'F' && rgb[0] && rgb[1] && rgb[2])
//		colors->floor_color = color_rgba(ft_atoi(rgb[0]),
//				ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
		colors->floor_color = color_rgba(255, ft_atoi(rgb[2]),
				ft_atoi(rgb[1]), ft_atoi(rgb[0]));
	else if (*line == 'C' && rgb[0] && rgb[1] && rgb[2])
//		colors->ceiling_color = color_rgba(ft_atoi(rgb[0]),
//				ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
		colors->ceiling_color = color_rgba(255, ft_atoi(rgb[2]),
				ft_atoi(rgb[1]), ft_atoi(rgb[0]));
	else
		cub3d_error("Invalid color1", 1);
	double_free(rgb);
	double_free(split);
	return (1);
}

int	parse_options(char *line, t_cub3d *cub3d)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \n"); //PREGUNTA: ¿Por qué ft_strtrim si la línea viene de GNL, luego no tiene \n?
	if (!tmp)
		cub3d_error("malloc", 1);
	if (ft_strnstr(tmp, "NO", 2) == tmp || ft_strnstr(tmp, "SO", 2) == tmp
		|| ft_strnstr(tmp, "EA", 2) == tmp || ft_strnstr(tmp, "WE", 2) == tmp)
		return (parse_textures(tmp, &cub3d->textures));
	else if (*tmp == 'F' || *tmp == 'C')
		return (parse_colors(tmp, &cub3d->colors));
//	else if (*tmp != '\0')
//		cub3d_error("Invalid line", 1);
	return (0);
}
