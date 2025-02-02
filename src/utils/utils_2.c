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

int	transp(uint32_t color)
{
	int	r;
	int	g;
	int	b;

	r = color & 0xff;
	g = (color >> 8) & 0xff;
	b = (color >> 16) & 0xff;
	if (abs(r - g) > 0x10 || abs(r - b) > 0x10 || abs(g - b) > 0x10
		|| r + g + b < 0x140)
		return (0);
	return ((r + g + b - 0x140) * 6 / 11 + 13);
}

void transparent_pixel(uint8_t *pixel, uint32_t color)
{
	int		alpha;
	uint32_t	tmp;

	alpha = 0xff - transp(color);
	tmp = *pixel * (255 - alpha);
	tmp += (color & 0xff) * alpha;
	tmp = (tmp + 127) / 255;
	*pixel = tmp;
	
	tmp = *++pixel * (255 - alpha);
	tmp += (color >> 8 & 0xff) * alpha;
	tmp = (tmp + 127) / 255;
	*pixel = tmp;
	
	tmp = *++pixel * (255 - alpha);
	tmp += (color >> 16 & 0xff) * alpha;
	tmp = (tmp + 127) / 255;
	*pixel = tmp;

/*	alpha = color & 0xff;
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
	*pixel = tmp;*/
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
