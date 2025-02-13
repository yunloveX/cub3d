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
}

void	blend_images(mlx_image_t *dst, mlx_texture_t *src, int scale)
{
	uint8_t		*src_pixel;
	uint32_t	color;
	int			i;
	int			j;

	ft_memset(dst->pixels, 0, dst->width * dst->height * sizeof(uint32_t));
	i = -1;
	while (++i < (int) src->width)
	{
		j = -1;
		while (++j < (int) src->height)
		{
			src_pixel = &src->pixels[(j * src->width + i) * 4];
			color = color_from_mem(src_pixel);
			if (color & 0xFF000000)
				put_scaled_pixel(dst, (int [2]){i * scale, j * scale},
					color, scale);
		}
	}
}

void	sprite(t_cub3d *cub3d)
{
	mlx_texture_t	*frame;
	int				y_pos;
	int				x_pos;

	frame = cub3d->hand_frame->content;
	x_pos = WIDTH / 2 - (frame->width * SCALE) / 2;
	y_pos = HEIGHT - (frame->height * SCALE) + 15;
	blend_images(cub3d->img_hands, frame, SCALE);
	mlx_image_to_window(cub3d->mlx, cub3d->img_hands, x_pos, y_pos);
	if (cub3d->hand_playing)
	{
		cub3d->hand_frame = cub3d->hand_frame->next;
		if (cub3d->hand_frame == NULL)
		{
			cub3d->hand_frame = *(cub3d->hand_texture);
			blend_images(cub3d->img_hands, cub3d->hand_frame->content, SCALE);
			mlx_image_to_window(cub3d->mlx, cub3d->img_hands, x_pos, y_pos);
		}
	}
}
