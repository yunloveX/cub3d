/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <israel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/01/04 17:51:23 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void transparent_pixel(uint8_t *pixel, uint32_t color)
{
	int		alpha;
	uint32_t	tmp;

	alpha = 255 - (color & 0xff);
	tmp = *pixel * (255 - alpha);
	tmp += (color >> 24 & 0xff) * alpha;
	tmp = (tmp + 127) / 255;
	*pixel = tmp;
	tmp = *++pixel * (255 - alpha);
	tmp += (color >> 16 & 0xff) * alpha;
	tmp = (tmp + 127) / 255;
	*pixel = tmp;
	tmp = *++pixel * (255 - alpha);
	tmp += (color >> 8 & 0xff) * alpha;
	tmp = (tmp + 127) / 255;
	*pixel = tmp;
}

void blend_images(mlx_image_t* base, mlx_texture_t* overlay, int x_offset, int y_offset)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	base_x;
	uint32_t	base_y;

	y = -1;
	while (++y < overlay->height)
	{
		base_y = y + y_offset;
		if (base_y >= base->height)
			continue;
		x = -1;
		while (++x < overlay->width)
		{
			base_x = x + x_offset;
			if (base_x >= base->width)
				continue;
			transparent_pixel(base->pixels + 4 * (base_y * base->width + base_x),
				((uint32_t*)overlay->pixels)[y * overlay->width + x]);
		}
	}
}
