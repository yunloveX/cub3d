/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawUtils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:41 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 13:00:14 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	put_map_dot(t_cub3d *cub3d, int x, int y, int color)
{
	int		i;
	int		j;

	x++;
	y++;
	i = 0;
	while (i < MAP_SCALE)
	{
		j = 0;
		while (j < MAP_SCALE)
		{
			transparent_pixel(cub3d->img->pixels + 4 * ((y * MAP_SCALE + j)
					* WIDTH + x * MAP_SCALE + i), color);
			j++;
		}
		i++;
	}
}

static uint8_t	darkness(int y, int height)
{
	uint8_t		dark_y;

	if (y < 10)
		dark_y = 28 * y;
	else if (height - y < 10)
		dark_y = 28 * (height - y);
	else
		dark_y = 255;
	return (dark_y);
}

static void	light_part(uint32_t *color, uint8_t fraction)
{
	uint32_t	tmp;

	tmp = (*color & 0xff00) >> 8;
	tmp *= fraction;
	tmp = (tmp + (tmp >> 8) + 0x80) >> 8;
	*color = (*color & 0xffff00ff) | (tmp << 8);
	tmp = (*color & 0xff0000) >> 16;
	tmp *= fraction;
	tmp = (tmp + (tmp >> 8) + 0x80) >> 8;
	*color = (*color & 0xff00ffff) | (tmp << 16);
	tmp = (*color & 0xff000000) >> 24;
	tmp *= fraction;
	tmp = (tmp + (tmp >> 8) + 0x80) >> 8;
	*color = (*color & 0x00ffffff) | (tmp << 24);
}

static uint32_t	pixel_color(t_cub3d *cub3d, double tx_h,
				double tx_v, int side)
{
	int				x;
	int				y;
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = cub3d->textures[side];
	x = (int)(tx_h * texture->width);
	y = (int)(tx_v * texture->height);
	color = color_from_mem(texture->pixels + 4 * (y * texture->width + x));
	light_part(&color, darkness(y, texture->height));
	return (color);
}

void	drawline(t_cub3d *cub3d, double tx_h, double dist, int side_height[2])
{
	int			v;
	double		tx_v;
	double		lim;

	lim = 0.5 / dist * sqrt(CAM_DIST * CAM_DIST
			+ side_height[1] * side_height[1]);
	v = -1;
	while (++v <= (HEIGHT + 1) / 2 - lim)
	{
		mlx_put_pixel(cub3d->img, side_height[1] + WIDTH / 2, v,
			cub3d->colors.ceiling_color);
		mlx_put_pixel(cub3d->img, side_height[1] + WIDTH / 2, HEIGHT - 1 - v,
			cub3d->colors.floor_color);
	}
	v--;
	while (++v < (HEIGHT + 1) / 2)
	{
		tx_v = (2 * v - HEIGHT) / (4 * lim) + 0.5;
		mlx_put_pixel(cub3d->img, side_height[1] + WIDTH / 2, v,
			pixel_color(cub3d, tx_h, tx_v, side_height[0]));
		mlx_put_pixel(cub3d->img, side_height[1] + WIDTH / 2, HEIGHT - 1 - v,
			pixel_color(cub3d, tx_h, 1 - tx_v, side_height[0]));
	}
}
