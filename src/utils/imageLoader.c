/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageLoader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/13 08:42:30 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	create_map_image(t_cub3d *cub3d)
{
	int			i;
	int			j;
	char		c;
	int			eol;
	uint32_t	color;

	cub3d->img_map = ft_calloc(1, sizeof(mlx_texture_t));
	if (!cub3d->img_map)
		cub3d_error("malloc", 1, cub3d);
	cub3d->img_map->width = cub3d->map.width + 2;
	cub3d->img_map->height = cub3d->map.height + 2;
	cub3d->img_map->bytes_per_pixel = 4;
	cub3d->img_map->pixels = ft_calloc(cub3d->img_map->width
			* cub3d->img_map->height, 4 * sizeof(uint8_t));
	if (!cub3d->img_map->pixels)
		cub3d_error("malloc", 1, cub3d);
	j = 0;
	while (j < cub3d->map.height + 2)
	{
		eol = 0;
		i = 0;
		while (i < cub3d->map.width + 2)
			{
			if (i == 0 || i == cub3d->map.width + 1
				|| j == 0 || j == cub3d->map.height + 1)
				color = 0xc0ffffff;
			else
			{
				if (eol)
					c = '0';
				else
				c = cub3d->map.grid[j - 1][i - 1];
				if (!c)
					eol = 1;
				if (c == '1')
					color = 0xff000000;
				else if (c == 'D')
					color = 0xff00ff00;
				else if (eol || c == '0' || c == ' ')
					color = 0xc0ffffff;
				else 
					color = 0xff0000ff;
			}
			mlx_draw_pixel(&cub3d->img_map->pixels[(j * cub3d->img_map->width + i) * 4], color);
			i++;
		}
		j++;
	}
}
/*
static void	put_scaled_pixel(mlx_image_t *dst, int ds[2],
	uint32_t color, int scale)
{
	int	si;
	int	sj;

	si = -1;
	while (++si < scale)
	{
		sj = -1;
		while (++sj < scale)
		{
			if (ds[0] + si < (int) dst->width
				&& ds[1] + sj < (int) dst->height)
				mlx_put_pixel(dst, ds[0] + si, ds[1] + sj, color);
		}
	}
}*/

void	blend_images(mlx_image_t *dst, uint32_t x0, uint32_t y0, mlx_texture_t *src, int scale)
{
	uint8_t		*dst_pixel;
	uint32_t	color;
	int			i;
	int			j;

	j = 0;
	while (j / scale < (int) src->height)
	{
		i = 0;
		while (i / scale < (int) src->width)
		{
			dst_pixel = &dst->pixels[((y0 + j) * dst->width + x0 + i) * 4];
			//color = color_from_mem(src->pixels + (j / scale * src->width + i / scale) * 4);
			color = *(uint32_t *)(src->pixels + (j / scale * src->width + i / scale) * 4);
			transparent_pixel(dst_pixel, color);
			i++;
		}
		j++;
	}
}

void	sprite(t_cub3d *cub3d)
{
	mlx_texture_t	*frame;
	int				x_pos;
	int				y_pos;

	frame = cub3d->hand_frame->content;
	x_pos = WIDTH / 2 - (frame->width / 2) * SCALE;
	y_pos = HEIGHT - (frame->height) * SCALE;
	blend_images(cub3d->img, x_pos, y_pos, frame, SCALE);
}
