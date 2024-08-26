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

static int	parse_textures(char *line, t_walls *walls, void *mlx)
{
	char	**path;

	path = ft_split(line, ' ');
	if (!path)
		cub3d_error("malloc", 1);
	if (!path[0] || !path[1])
		cub3d_error("Invalid texture path", 1);
	if (*line == 'N' && !walls->north.img)
		walls->north.img = mlx_xpm_file_to_image(mlx, path[1],
				&walls->north.width, &walls->north.height);
	else if (*line == 'S' && !walls->south.img)
		walls->south.img = mlx_xpm_file_to_image(mlx, path[1],
				&walls->south.width, &walls->south.height);
	else if (*line == 'W' && !walls->west.img)
		walls->west.img = mlx_xpm_file_to_image(mlx, path[1],
				&walls->west.width, &walls->west.height);
	else if (*line == 'E' && !walls->east.img)
		walls->east.img = mlx_xpm_file_to_image(mlx, path[1],
				&walls->east.width, &walls->east.height);
	else
		cub3d_error("Invalid texture", 1);
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
		colors->floor_color = create_trgb(0, ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else if (*line == 'C' && rgb[0] && rgb[1] && rgb[2])
		colors->ceiling_color = create_trgb(0, ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		cub3d_error("Invalid color", 1);
	if (colors->floor_color < 0 || colors->ceiling_color < 0)
		cub3d_error("Invalid color", 1);
	double_free(rgb);
	double_free(split);
	return (1);
}

int	parse_options(char *line, t_cub3d *cub3d)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \n");
	if (!tmp)
		cub3d_error("malloc", 1);
	if (*tmp == 'N' || *tmp == 'S' || *tmp == 'E' || *tmp == 'W')
		return (parse_textures(tmp, &cub3d->textures, cub3d->mlx));
	else if (*tmp == 'F' || *tmp == 'C')
		return (parse_colors(tmp, &cub3d->colors));
	else if (*tmp != '\0')
		cub3d_error("Invalid line", 1);
	return (0);
}
