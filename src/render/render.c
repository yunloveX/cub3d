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
#include "quatlib.h"

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
//		*color = ((uint32_t *)cub3d->textures.south.img)[point];
		*color = 0xFF0000FF;
		return ('s');
	}
	if (j > 0 && cub3d->map.grid
		[(int) floor(0.5 - progress.j)][(int) floor(progress.i)] == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.north.height;
		point *= cub3d->textures.north.width;
		point += (ceil(progress.i) - progress.i) * cub3d->textures.north.width;
//		*color = ((uint32_t *)cub3d->textures.north.img)[point];
		*color = 0x0000FFFF;
		return ('n');
	}
	return ('\0');
}

uint32_t	color_east_west(
			t_cub3d *cub3d, t_quaternion progress, float i, uint32_t *color)
{
	int	pixel;

	if (i < 0 && cub3d->map.grid
		[(int) floor(-progress.j)][(int) floor(progress.i - 0.5)] == '1')
	{
		pixel = (ceil(progress.k) - progress.k) * cub3d->textures.east.height;
		pixel *= cub3d->textures.east.width;
		pixel += (ceil(progress.j) - progress.j) * cub3d->textures.east.width;
//		*color = ((uint32_t *)cub3d->textures.east.img)[pixel];
		*color = 0x00FF00FF;
		return ('e');
	}
	if (i > 0 && cub3d->map.grid
		[(int) floor(-progress.j)][(int) floor(progress.i + 0.5)] == '1')
	{
		pixel = (ceil(progress.k) - progress.k) * cub3d->textures.west.height;
		pixel *= cub3d->textures.west.width;
		pixel += (progress.j - floor(progress.j)) * cub3d->textures.west.width;
//		*color = ((uint32_t *)cub3d->textures.west.img)[pixel];
		*color = 0x00FFFFFF;
		return ('w');
	}
	return ('\0');
}

char	meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray, uint32_t *color)
{
	int	x;
	int	y;

	if (progress.k >= 1.0)
	{
		*color = cub3d->colors.ceiling_color;
		return ('c');
	}
	if (progress.k <= 0.0)
	{
		*color = cub3d->colors.floor_color;
		return ('f');
	}
	x = progress.i;
	y = -progress.j;
	if (x == floor(x))
		return (color_east_west(cub3d, progress, ray.i, color));
	if (y == floor(y))
		return (color_north_south(cub3d, progress, ray.j, color));
	return ('\0');
}

t_quaternion	q_gaps(t_quaternion point, t_quaternion dir)
{
	t_quaternion	ret;

	ret.r = 0.0;
	ret.i = ceil(point.i) - point.i;
	if (dir.i < 0)
		ret.i = ret.i - 1;
	else if (ret.i == 0)
		ret.i = 1;
	ret.j = ceil(point.j) - point.j;
	if (dir.j < 0)
		ret.j = ret.j - 1;
	else if (ret.j == 0)
		ret.j = 1;
	ret.k = ceil(point.k) - point.k;
	if (dir.k < 0)
		ret.k = ret.k - 1;
	else if (ret.k == 0)
		ret.k = 1;
	return (ret);
}

double	min_jump(t_quaternion gap, t_quaternion dir)
{
	double	jump_i;
	double	jump_j;
	double	jump_k;

	jump_i = FAR;
	jump_j = FAR;
	jump_k = FAR;
	if (dir.i)
		jump_i = gap.i / dir.i;
	if (dir.j)
		jump_j = gap.j / dir.j;
	if (dir.k)
		jump_k = gap.k / dir.k;
//	printf("jump_i: %f\n", jump_i);
//	printf("jump_j: %f\n", jump_j);
//	printf("jump_k: %f\n", jump_k);
	if (jump_i > 0 && jump_i < FAR && jump_i <= jump_j && jump_i <= jump_k)
		return (jump_i);
	if (jump_j > 0 && jump_j < FAR && jump_j <= jump_i && jump_j <= jump_k)
		return (jump_j);
	if (jump_k > 0 && jump_k < FAR && jump_k <= jump_i && jump_k <= jump_j)
		return (jump_k);
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
		gap = q_gaps(progress, ray);
		jump += min_jump(gap, ray);
//		printf("jump: %f\n", jump);
		progress = q_add(cub3d->player.cam, q_scale(ray, jump));
//		printf("progress: %f %f %f\n", progress.i, progress.j, progress.k);
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
		while(v < -20)
		{
			if (v || h)
				mlx_put_pixel(cub3d->img, h + WIDTH / 2, v + HEIGHT / 2, raycast(cub3d, h, v));
			v++;
		}
		h++;
	}
}