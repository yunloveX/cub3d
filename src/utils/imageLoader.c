/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageLoader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/14 10:01:37 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#define X 0
#define Y 1

void	blend_images(mlx_image_t *dst, uint32_t x_y[2],
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
			dst_pixel = &dst->pixels[((x_y[1] + j)
					* dst->width + x_y[0] + i) * 4];
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
	x_pos = WIDTH / 2 - (frame->width / 2) * SCALE;
	y_pos = HEIGHT - (frame->height) * SCALE;
	blend_images(cub3d->img, (uint32_t [2]){x_pos, y_pos}, frame, SCALE);
}
