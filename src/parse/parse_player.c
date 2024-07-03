/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:52:08 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 13:11:14 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_position_player(t_cub3d *cub3d, int i, char c)
{
	int	j;

	j = 0;
	while (cub3d->map.grid[i][j])
	{
		if (cub3d->map.grid[i][j] == c)
		{
			cub3d->player.x = j;
			cub3d->player.y = i;
			cub3d->player.dir_y = 0;
			if (c == 'N')
				cub3d->player.dir_x = 90;
			else if (c == 'S')
				cub3d->player.dir_x = 270;
			else if (c == 'W')
				cub3d->player.dir_x = 180;
			else if (c == 'E')
				cub3d->player.dir_x = 0;
		}
		j++;
	}
}

void	parse_player(t_cub3d *cub3d)
{
	int		i;

	i = 0;
	cub3d->player.x = -1;
	while (i < cub3d->map.height)
	{
		if (ft_strchr(cub3d->map.grid[i], 'N') && cub3d->player.x == -1)
			parse_position_player(cub3d, i, 'N');
		else if (ft_strchr(cub3d->map.grid[i], 'S') && cub3d->player.x == -1)
			parse_position_player(cub3d, i, 'S');
		else if (ft_strchr(cub3d->map.grid[i], 'W') && cub3d->player.x == -1)
			parse_position_player(cub3d, i, 'W');
		else if (ft_strchr(cub3d->map.grid[i], 'E') && cub3d->player.x == -1)
			parse_position_player(cub3d, i, 'E');
		else if ((ft_strchr(cub3d->map.grid[i], 'N')
				|| ft_strchr(cub3d->map.grid[i], 'S')
				|| ft_strchr(cub3d->map.grid[i], 'W')
				|| ft_strchr(cub3d->map.grid[i], 'E')) && cub3d->player.x != -1)
			cub3d_error("Error\nMultiple players found", 1);
		i++;
	}
	if (cub3d->player.x == -1)
		cub3d_error("Error\nNo player found", 1);
}
