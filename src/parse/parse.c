/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <israel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:36:48 by yunlovex          #+#    #+#             */
/*   Updated: 2025/01/04 18:05:05 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse(t_cub3d *cub3d, char *file)
{
    int     fd;
    int     options;
    char    *line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        cub3d_error(file, 1);
    line = get_next_line(fd);
    options = 0;
    while (line && options < 8)
    {
        options += parse_options(line, cub3d);
        line = get_next_line(fd);
    }
	if (parse_map(fd, &cub3d->map) == EXIT_FAILURE)
		cub3d_error("Invalid map", 1);
    close(fd);
    parse_player(cub3d);

}