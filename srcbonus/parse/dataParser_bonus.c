/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataParser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:36:48 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/16 12:59:43 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

void	parse(t_cub3d *cub3d, char *file)
{
	int		fd;
	int		options;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		cub3d_error(file, 1, cub3d);
	line = get_next_line(fd);
	options = 0;
	while (line && options < 8)
	{
		options += parse_options(line, cub3d);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (options < 8)
		cub3d_error("Error\nMissing options", 1, cub3d);
	if (parse_map(fd, &cub3d->map) == EXIT_FAILURE)
		cub3d_error("Error\nInvalid map", 1, cub3d);
	create_map_image(cub3d);
	close(fd);
	parse_player(cub3d);
}
