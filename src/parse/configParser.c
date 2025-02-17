/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:07 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/17 08:30:54 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(char **path, mlx_texture_t *textures[5])
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path[1]);
	if (!texture)
		return (EXIT_FAILURE);
	if (!ft_strcmp(path[0], "NO") && !textures[0])
		textures[0] = texture;
	else if (!ft_strcmp(path[0], "SO") && !textures[2])
		textures[2] = texture;
	else if (!ft_strcmp(path[0], "EA") && !textures[1])
		textures[1] = texture;
	else if (!ft_strcmp(path[0], "WE") && !textures[3])
		textures[3] = texture;
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_textures(char *line, mlx_texture_t *textures[5])
{
	char	**path;

	path = ft_split(line, ' ');
	if (!path)
		return (printf("malloc\n"), 0);
	if (!path[0] || !path[1])
		return (double_free(path), 0);
	if (path[2])
		return (double_free(path), 0);
	if (load_texture(path, textures))
		return (double_free(path), 0);
	return (double_free(path), 1);
}

static int	parse_colors(char *line, t_colors *colors)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		return (printf("malloc\n"), 0);
	if (!split[1])
		return (double_free(split), 0);
	rgb = ft_split(split[1], ',');
	if (!rgb)
		return (printf("malloc\n"), double_free(split), 0);
	if (*line == 'F' && rgb[0] && rgb[1] && rgb[2] && !rgb[3])
		colors->floor_color = color_rgba(ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	else if (*line == 'C' && rgb[0] && rgb[1] && rgb[2] && !rgb[3])
		colors->ceiling_color = color_rgba(ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	else
		return (double_free(rgb), double_free(split), 0);
	return (double_free(rgb), double_free(split), 1);
}

int	parse_options(char *line, t_cub3d *cub3d)
{
	char	*tmp;
	int		ret;

	tmp = ft_strtrim(line, " \n");
	if (!tmp)
		cub3d_error("malloc", 1, cub3d);
	ret = 0;
	if (ft_strnstr(tmp, "NO", 2) == tmp || ft_strnstr(tmp, "SO", 2) == tmp
		|| ft_strnstr(tmp, "EA", 2) == tmp || ft_strnstr(tmp, "WE", 2) == tmp)
		ret = parse_textures(tmp, cub3d->textures);
	else if (*tmp == 'F' || *tmp == 'C')
		ret = parse_colors(tmp, &cub3d->colors);
	free(tmp);
	return (ret);
}
