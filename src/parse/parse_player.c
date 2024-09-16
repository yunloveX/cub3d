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

static void	locate_player(t_cub3d *cub3d, int i, int j)
{
	char	c;

	cub3d->player.x = 0.5 + j;
	cub3d->player.y = 0.5 + i;
	cub3d->player.z = 0.5;
	cub3d->player.dir_x = 0;
	cub3d->player.dir_y = 0;
	cub3d->player.dir_z = 0;
	c = cub3d->map.grid[i][j];
	if (c == 'N')
		cub3d->player.dir_y = -1.0;
	if (c == 'S')
		cub3d->player.dir_y = 1.0;
	if (c == 'E')
		cub3d->player.dir_x = 1.0;
	if (c == 'W')
		cub3d->player.dir_x = -1.0;
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	parse_player(t_cub3d *cub3d)
{
	int		i;
	int		j;

	i = 0;
	cub3d->player.x = NO_PLAYER;
	while (i < cub3d->map.height)
	{
		j = 0;
		while (cub3d->map.grid[i][j])
		{
			if (is_player(cub3d->map.grid[i][j]))
			{
				if (cub3d->player.x != NO_PLAYER)
					cub3d_error("Error\nMultiple players found", 1);
				locate_player(cub3d, i, j);
			}
			j++;
		}
		i++;
	}
	if (cub3d->player.x == NO_PLAYER)
		cub3d_error("Error\nNo player found", 1);
}
