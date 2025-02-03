/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:19:41 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/03 12:21:12 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Creates a 32-bit rgba color from its constituents.
 *
 * @details This function creates a single unsigned 32-bit color value created from
 * its four constituents, red (most significant byte), green, blue and alpha
 * (less significant byte). Params are unsigned 8-bit integers.
 *
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 * @param a The alpha component (complementary of transparency).
 * @return unsigned 32-bit value.
 */

uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color_from_mem(uint8_t *pixel)
{
	uint32_t	color;

	color = 0;
	color |= ((uint32_t)*pixel++) << 24;
	color |= ((uint32_t)*pixel++) << 16;
	color |= ((uint32_t)*pixel++) << 8;
	color |= (uint32_t)*pixel;
	return (color);
}

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
}