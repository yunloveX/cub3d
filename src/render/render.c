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

uint32_t	color_north_south(
			t_cub3d *cub3d, t_quaternion progress, float j, uint32_t *color)
{
	int	point;

	if (j < 0 && cub3d->map.grid
		[(int) floor(0.5 - progress.j)][(int) floor(progress.i)] == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.south.height;
		point *= cub3d->textures.south.width;
		point += (progress.i - floor(progress.i)) * cub3d->textures.south.width;
		*color = ((uint32_t *)cub3d->textures.south.img)[point];
		return ('s');
	}
	if (j > 0 && cub3d->map.grid
		[(int) floor(0.5 - progress.j)][(int) floor(progress.i)] == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.north.height;
		point *= cub3d->textures.north.width;
		point += (ceil(progress.i) - progress.i) * cub3d->textures.north.width;
		*color = ((uint32_t *)cub3d->textures.north.img)[point];
		return ('n');
	}
	return ('/0');
}

uint32_t	color_east_west(
			t_cub3d *cub3d, t_quaternion progress, float i, uint32_t *color)
{
	int	point;

	if (i < 0 && cub3d->map.grid
		[(int) floor(-progress.j)][(int) floor(progress.i - 0.5)] == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.east.height;
		point *= cub3d->textures.east.width;
		point += (ceil(progress.j) - progress.j) * cub3d->textures.east.width;
		*color = ((uint32_t *)cub3d->textures.east.img)[point];
		return ('e');
	}
	if (i > 0 && cub3d->map.grid
		[(int) floor(-progress.j)][(int) floor(progress.i + 0.5)] == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.west.height;
		point *= cub3d->textures.west.width;
		point += (progress.j - floor(progress.j)) * cub3d->textures.west.width;
		*color = ((uint32_t *)cub3d->textures.west.img)[point];
		return ('w');
	}
	return ('/0');
}

uint32_t	check_k(t_cub3d *cub3d, float k)
{
	if (k >= 1.0)
		return (cub3d->colors.ceiling_color);
	if (k <= 0.0)
		return (cub3d->colors.floor_color);
	return (0);
}

char	meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray, uint32_t *color)
{
	int	x;
	int	y;

	if (progress.k >= 1.0)
	{
		*color = check_k(cub3d, progress.k);
		return ('c');
	}
	x = progress.i;
	y = -progress.j;
	if (x == floor(x))
		return (color_east_west(cub3d, progress, ray.i, color));
	if (y == floor(y))
		return (color_north_south(cub3d, progress, ray.j, color));
	return ('/0');
}

t_quaternion	q_part(t_quaternion p, t_quaternion r)
{
	t_quaternion	s;

	s.r = 0.0;
	s.i = ceil(p.i) - p.i;
	if (r.i < 0)
		s.i = s.i - 1;
	else if (s.i == 0)
		s.i = 1;
	s.j = ceil(p.j) - p.j;
	if (r.j < 0)
		s.j = s.j - 1;
	else if (s.j == 0)
		s.j = 1;
	s.k = ceil(p.k) - p.k;
	if (r.k < 0)
		s.k = s.k - 1;
	else if (s.k == 0)
		s.k = 1;
	return (s);
}

double	min_non_zero(t_quaternion a, t_quaternion b)
{
	double	x;
	double	y;
	double	z;

	x = FAR;
	y = FAR;
	z = FAR;
	if (b.i)
		x = a.i / b.i;
	if (b.j)
		y = a.j / b.j;
	if (b.k)
		z = a.k / b.k;
	if (x > 0 && x < FAR && x <= y && x <= z)
		return (x);
	if (y > 0 && y < FAR && y <= x && y <= z)
		return (y);
	if (z > 0 && z < FAR && z <= x && z <= y)
		return (z);
	return (0);
}

uint32_t	intersect(t_cub3d *cub3d, t_quaternion ray)
{
	t_quaternion	gap;
	t_quaternion	progress;
	double		jump; 
	uint32_t	color;

	jump = 0.0;
	progress = cub3d->player.cam;
	while (1)
	{
		gap = q_part(progress, ray);
		jump += min_non_zero(gap, ray);
		progress = q_add(cub3d->player.cam, q_scale(ray, jump));
		if (meet_wall(cub3d, progress, ray, &color))
			return (color);
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