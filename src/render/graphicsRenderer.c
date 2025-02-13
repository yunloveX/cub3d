/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsRenderer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:16:50 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/13 09:47:37 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_map_dot(t_cub3d *cub3d, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			transparent_pixel(cub3d->img->pixels + 4 * ((y * 5 + j)
					* WIDTH + x * 5 + i), color);
			j++;
		}
		i++;
	}
}

static void	show_map(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		color;

	y = -2;
	while (++y < cub3d->map.height + 1)
	{
		x = -2;
		while (++x < cub3d->map.width + 1)
		{
			if (x == (int) cub3d->player.pos.i
				&& y == (int) -cub3d->player.pos.j)
				color = 0xff0000ff;
			else if (x < 0 || x == cub3d->map.width || y < 0
				|| y == cub3d->map.height || cub3d->map.grid[y][x] != '1')
				color = 0x00ffffff;
			else
				color = 0x00000000;
			put_map_dot(cub3d, x + 1, y + 1, color);
		}
	}
}

void	render(t_cub3d *cub3d)
{
	int		h;
	int		side;
	double	dist;
	double	tx_h;

	memset(cub3d->img->pixels, 0, WIDTH * HEIGHT * sizeof(uint32_t));
	h = -WIDTH / 2 - 1;
	while (++h < WIDTH / 2)
	{
		side = raycast(cub3d, h, &tx_h, &dist);
		if (side < 0)
			break ;
		drawline(cub3d, tx_h, dist, (int [2], {side, h}));
	}
	if (side < 0)
	{
		player_equal(&cub3d->player, &cub3d->player_old);
		return ;
	}
	player_equal(&cub3d->player_old, &cub3d->player);
	show_map(cub3d);
	cub3d->frames_shown++;
}
