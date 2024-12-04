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



static void	locate_player(t_cub3d *cub3d, int y, int x)
{
	char	c;

	cub3d->player.pos.i = 0.5 + x;
	cub3d->player.pos.j = -0.5 - y;
	cub3d->player.pos.k = 0.5;
	q_zero(&cub3d->player.down);
	cub3d->player.down.k = -1.0 / CUBE_EDGE;
	q_zero(&cub3d->player.right);
	c = cub3d->map.grid[y][x];
	if (c == 'N')
		cub3d->player.right.i = 1.0 / CUBE_EDGE;
	if (c == 'S')
		cub3d->player.right.i = -1.0 / CUBE_EDGE;
	if (c == 'E')
		cub3d->player.right.j = -1.0 / CUBE_EDGE;
	if (c == 'W')
		cub3d->player.right.j = 1.0 / CUBE_EDGE;
	printf("right: %f, %f, %f\n", cub3d->player.right.i, cub3d->player.right.j, cub3d->player.right.k);
	printf("down: %f, %f, %f\n", cub3d->player.down.i, cub3d->player.down.j, cub3d->player.down.k);
	locate_cam(cub3d);
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	parse_player(t_cub3d *cub3d)
{
	int		y;
	int		x;

	y = 0;
	q_zero(&cub3d->player.pos);
	while (y < cub3d->map.height)
	{
		x = 0;
		while (cub3d->map.grid[y][x])
		{
			if (is_player(cub3d->map.grid[y][x]))
			{
				if (cub3d->player.pos.k)
					cub3d_error("Error\nMultiple players found", 1);
				locate_player(cub3d, y, x);
			}
			x++;
		}
		y++;
	}
	if (!cub3d->player.pos.k)
		cub3d_error("Error\nNo player found", 1);
}
