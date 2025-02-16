/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageLoader_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/16 13:00:14 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

#define X 0
#define Y 1

static void	map_alloc(t_cub3d *cub3d)
{
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
}

static uint32_t	map_color(char c)
{
	if (c == '1')
		return (0xff000000);
	else if (c == 'D')
		return (0xff00ff00);
	else
		return (0xc0ffffff);
}

void	create_map_image(t_cub3d *cub3d)
{
	int			i;
	int			j;
	char		c;
	int			eol;

	map_alloc(cub3d);
	j = -1;
	while (++j < cub3d->map.height + 2)
	{
		eol = 0;
		i = -1;
		while (++i < cub3d->map.width + 2)
		{
			if (eol || i == 0 || i == cub3d->map.width + 1
				|| j == 0 || j == cub3d->map.height + 1)
				c = '0';
			else
				c = cub3d->map.grid[j - 1][i - 1];
			if (!c)
				eol = 1;
			((uint32_t *)cub3d->img_map->pixels)
			[j * cub3d->img_map->width + i] = map_color(c);
		}
	}
}

void	blend_images(mlx_image_t *dst, uint32_t position[2],
			mlx_texture_t *src, int scale)
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
			dst_pixel = &dst->pixels[((position[Y] + j)
					* dst->width + position[X] + i) * 4];
			color = *(uint32_t *)(src->pixels
					+ (j / scale * src->width + i / scale) * 4);
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
	x_pos = WIDTH / 2 - (frame->width / 2) * SPRITE_SCALE;
	y_pos = HEIGHT - (frame->height) * SPRITE_SCALE;
	blend_images(cub3d->img, (uint32_t [2]){x_pos, y_pos}, frame, SPRITE_SCALE);
}
