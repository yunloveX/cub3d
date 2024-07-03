/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:36:48 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 08:35:14 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse(t_cub3d *cub3d, char *file)
{
	int		fd;
	int		options;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		cub3d_error(file, 1);
	options = 0;
	line = get_next_line(fd);
	while (line && options < 6)
	{
		options += parse_options(line, cub3d);
		free(line);
		line = get_next_line(fd);
	}
	parse_map(fd, &cub3d->map);
	close(fd);
	parse_player(cub3d);
}
