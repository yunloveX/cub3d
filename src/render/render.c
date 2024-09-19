/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:16:50 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 13:17:16 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO render
/*
void	render(double xpos, double ypos, t_cub3d *cub3d)
{
	uint32_t	h;
	uint32_t	v;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	h = 0;
	v = 0;
	while (v < HEIGHT)
	{
		g = 256 * ((v + (int) ypos) % HEIGHT) / HEIGHT;
		h = 0;
		while (h < WIDTH)
		{
			r = 256 * ((h + (int) xpos) % WIDTH) / WIDTH;
			b = 255 - r - g;
			mlx_put_pixel(cub3d->img, h, v, color_rgba(r, g, b, 255));
			h++;
		}
		v++;
	}
}*/

t_quaternion	q_part(t_quaternion p, t_quaternion r)
{
	t_quaternion	s;

	s.r = 0.0;
	if (r.i > 0)
		s.i = ceil(p.i) - p.i;
	else
		s.i = p.i - floor(p.i);
	if (r.j > 0)
		s.j = ceil(p.j) - p.j;
	else
		s.j = p.j - floor(p.j);
	if (r.k > 0)
		s.k = ceil(p.k) - p.k;
	else
		s.k = p.k - floor(p.k);
	return (s);
}

double	min_non_zero(t_quaternion a, t_quaternion b)
{
	double	x;
	double	y;
	double	z;

	x = a.i / b.i;
	y = a.j / b.j;
	z = a.k / b.k;
	if (x > 0 && (x < y || y <= 0) && (x < z || z <= 0))
		return (x);
	if (y > 0 && (y < x || x <= 0) && (y < z || z <= 0))
		return (y);
	if (z > 0 && (z < x || x <= 0) && (z < y || y <= 0))
		return (z);
	return (0); //OJO!!! Si pasa exactmente por una esquina.
}	

uint32_t	intersect(t_cub3d *cub3d, t_quaternion ray)
{
	t_quaternion	net;
	t_quaternion	cut;
	double		jump;

	jump = 0.0;
	net = q_part(cub3d->player.pos, ray);
	while (1)
	{
		jump += min_non_zero(net, ray);
		net = q_sub(net, q_scale(ray, jump));
		cut = q_add(cub3d->player.pos, net);
		
	}	
	
}

uint32_t	raycast(t_cub3d *cub3d, int h, int v)
{
	t_quaternion	ray;

	ray = q_add(q_scale(cub3d->player.right, h),
		q_scale(cub3d->player.down, v));
	ray = q_add(cub3d->player.pos, ray);
	ray = q_sub(ray, cub3d->player.cam);
	return (intersect(cub3d, ray));
}

void	render(t_cub3d *cub3d)
{
	int	h;
	int	v;

	h = -WIDTH / 2;
	while(h < WIDTH / 2)
	{
		v = -HEIGHT / 2;
		while(v < HEIGHT / 2)
		{
			mlx_put_pixel(cub3d->img, h, v, raycast(cub3d, h, v));
			v++;
		}
		h++;
	}
}