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

char	map(t_cub3d *cub3d, int x, int y)
{
	if (x < 0 || y < 0 || x >= cub3d->map.width || y >= cub3d->map.height)
		return ('1');
	return (cub3d->map.grid[y][x]);
}

uint32_t	color_north_south(
			t_cub3d *cub3d, t_quaternion progress, float delta_j, uint32_t *color)
{
	int	point;
	int	x;
	int	y;

	x = (int) floor(progress.i);
	y = (int) floor(0.5 - progress.j);
//	if (j < 0 && cub3d->map.grid
//		[(int) floor(0.5 - progress.j)][(int) floor(progress.i)] == '1')
	if (delta_j < 0 && map(cub3d, x, y) == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.north->height;
		point *= cub3d->textures.north->width;
		point += (ceil(progress.i) - progress.i) * cub3d->textures.north->width;
		*color = ((uint32_t *)cub3d->textures.north->pixels)[point];
//		*color = 0xFF0000FF; //RED
		return ('n');
	}
	y--;
	if (delta_j > 0 && map(cub3d, x, y) == '1')
	{
		point = (ceil(progress.k) - progress.k) * cub3d->textures.south->height;
		point *= cub3d->textures.south->width;
		point += (progress.i - floor(progress.i)) * cub3d->textures.south->width;
		*color = ((uint32_t *)cub3d->textures.south->pixels)[point];
//		*color = 0x0000FFFF; //BLUE
		return ('s');
	}
	return ('\0');
}

uint32_t	color_east_west(
			t_cub3d *cub3d, t_quaternion progress, float delta_i, uint32_t *color)
{
	int	pixel;
	int	x;
	int	y;

	x = (int) floor(progress.i - 0.5);
	y = (int) floor(-progress.j);

	if (delta_i < 0 && map(cub3d, x, y) == '1')
	{
		pixel = (ceil(progress.k) - progress.k) * cub3d->textures.east->height;
		pixel *= cub3d->textures.east->width;
		pixel += (progress.j - floor(progress.j)) * cub3d->textures.east->width;
		*color = ((uint32_t *)cub3d->textures.east->pixels)[pixel];
//		*color = 0x00FF00FF; //GREEN
		return ('e');
	}
	x++;
	if (delta_i > 0 && map(cub3d, x, y) == '1')
	{
		pixel = (ceil(progress.k) - progress.k) * cub3d->textures.west->height;
		pixel *= cub3d->textures.west->width;
		pixel += (ceil(progress.j) - progress.j) * cub3d->textures.west->width;
		*color = ((uint32_t *)cub3d->textures.west->pixels)[pixel];
//		*color = 0x00FFFFFF; //CYAN
		return ('w');
	}
	return ('\0');
}

int	at_limit(double x)
{
	double	part;

	part = x - floor(x);
	if (part > 0.5)
		part = 1.0 - part;
	if (part < TOLERANCE)
		return (1);
	return (0);
}

char	meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray, uint32_t *color)
{
	if (progress.k > 0.9 && at_limit(progress.k - 1.0))
	{
		*color = cub3d->colors.ceiling_color;
		return ('c');
	}
	if (progress.k < 0.1 && at_limit(progress.k))
	{
		*color = cub3d->colors.floor_color;
		return ('f');
	}
	if (at_limit(progress.i))
		return (color_east_west(cub3d, progress, ray.i, color));
	if (at_limit(progress.j))
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
//	printf("******************ERROR: min_jump !!!************\n");
	return (0);
}

uint32_t	intersect(t_cub3d *cub3d, t_quaternion ray)
{
	t_quaternion	gap;
	t_quaternion	progress;
	double		jump; 
	double		d_jump; 
	uint32_t	color;

	jump = 1.0;
	progress = q_add(ray, cub3d->player.cam);
	while (1)
	{
		gap = q_gaps(progress, ray);
		d_jump = min_jump(gap, ray);
		if (d_jump == 0)
			return (0x888888FF); //GRAY
		jump += d_jump;
//		printf("jump: %f\n", jump);
		progress = q_add(cub3d->player.cam, q_scale(ray, jump));
//		printf("progress: %f %f %f\n", progress.i, progress.j, progress.k);
		if (meet_wall(cub3d, progress, ray, &color))
			return (color);
	}	
}
/*
	ray = q_add(q_scale(cub3d->player.right, h),
		q_scale(cub3d->player.down, v));
	ray = q_add(cub3d->player.pos, ray);
	ray = q_sub(ray, cub3d->player.cam);
*/
uint32_t	raycast(t_cub3d *cub3d, int h, int v)
{
	t_quaternion	ray;

	ray.r = 0;
	ray.i = cub3d->player.right.i * h + cub3d->player.down.i * v;
	ray.j = cub3d->player.right.j * h + cub3d->player.down.j * v;
	ray.k = cub3d->player.right.k * h + cub3d->player.down.k * v;
	ray.i += cub3d->player.pos.i - cub3d->player.cam.i;
	ray.j += cub3d->player.pos.j - cub3d->player.cam.j;
	ray.k += cub3d->player.pos.k - cub3d->player.cam.k;
	return (intersect(cub3d, ray));
}

void	render(t_cub3d *cub3d)
{
	int	h;
	int	v;
	uint32_t	color;

	h = -WIDTH / 2;
	while(h < WIDTH / 2)
	{
		v = -HEIGHT / 2;
		while(v < HEIGHT / 2)
		{
			color = raycast(cub3d, h, v);
//			if (color == 0x888888FF)
//				printf("h, v: %d %d\n", h, v);
			((uint32_t *)cub3d->img->pixels)[(v + HEIGHT / 2) * WIDTH + h + WIDTH / 2] = color;
//			mlx_put_pixel(cub3d->img, h + WIDTH / 2, v + HEIGHT / 2, color);
			v++;
		}
		h++;
	}
//	mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);
	cub3d->frames_shown++;
	printf("frames_shown: %d\n", cub3d->frames_shown);
}