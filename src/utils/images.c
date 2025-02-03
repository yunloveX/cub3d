/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/03 12:21:03 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
