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

int	wall_north_south(
			t_cub3d *cub3d, t_quaternion progress, float delta_j, double *tx_h)
{
	int	x;
	int	y;

	x = (int) floor(progress.i);
	y = (int) floor(0.5 - progress.j);
	if (delta_j < 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = ceil(progress.i) - progress.i;
		return (0);
	}
	y--;
	if (delta_j > 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = progress.i - floor(progress.i);
		return (2);
	}
	return (-1);
}

int	wall_east_west(
			t_cub3d *cub3d, t_quaternion progress, float delta_i, double *tx_h)
{
	int	x;
	int	y;

	x = (int) floor(progress.i - 0.5);
	y = (int) floor(-progress.j);

	if (delta_i < 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = ceil(progress.j) - progress.j;
		return (3);
	}
	x++;
	if (delta_i > 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = progress.j - floor(progress.j);
		return (1);
	}
	return (-1);
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

int	meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray, double *tx_h)
{
	if (at_limit(progress.i))
		return (wall_east_west(cub3d, progress, ray.i, tx_h));
	if (at_limit(progress.j))
		return (wall_north_south(cub3d, progress, ray.j, tx_h));
	return (-1);
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
	ret.k = 0;
	return (ret);
}

double	d_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

double	min_jump(t_cub3d *cub3d, t_quaternion *gap, t_quaternion dir)
{
	double	min;

	min = 0;
	if (d_abs(dir.i) > TOLERANCE)
		cub3d->jumps[0] = gap->i / dir.i;
	else
		cub3d->jumps[0] = FAR;
	if (d_abs(dir.j) > TOLERANCE)
		cub3d->jumps[1] = gap->j / dir.j;
	else
		cub3d->jumps[1] = FAR;
	if (cub3d->jumps[0] > 0 && cub3d->jumps[0] < FAR
		&& cub3d->jumps[0] <= cub3d->jumps[1])
		min = (cub3d->jumps[0]);
	else
		min = (cub3d->jumps[1]);
	if (min)
	{
		gap->i = gap->i - dir.i * min;
		if (gap->i * dir.i <= 0 && dir.i != 0)
			gap->i = dir.i / d_abs(dir.i);
		gap->j = gap->j - dir.j * min;
		if (gap->j * dir.j <= 0 && dir.j != 0)
			gap->j = dir.j / d_abs(dir.j);
	}
//	printf("******************ERROR: min_jump !!!************\n");
	return (min);
}

int	intersect(t_cub3d *cub3d, t_quaternion ray, double *tx_h, double *dist)
{
	t_quaternion	gap;
	t_quaternion	progress;
	double			d_jump;
	int				ret;

	*dist = q_norm(ray);
	progress = q_add(cub3d->player.cam, ray);
	q_normalize(&ray);
	gap = q_gaps(progress, ray);
	ret = meet_wall(cub3d, progress, ray, tx_h);
	while (ret < 0)
	{
		d_jump = min_jump(cub3d, &gap, ray);
		if (d_jump == 0)
			return (0); //Nunca debería pasar
		*dist += d_jump;
//		printf("jump: %f\n", d_jump);
		progress = q_add(cub3d->player.cam, q_scale(ray, *dist));
//		printf("progress: %f %f %f\n", progress.i, progress.j, progress.k);
		ret = meet_wall(cub3d, progress, ray, tx_h);
	}
	return (ret);
}
/*
	ray = q_add(q_scale(cub3d->player.right, h),
		q_scale(cub3d->player.down, v));
	ray = q_add(cub3d->player.pos, ray);
	ray = q_sub(ray, cub3d->player.cam);

side = raycast(cub3d, h, &tx_h, &dist);
*/
int	raycast(t_cub3d *cub3d, int h, double *tx_h, double *dist)
{
	t_quaternion	ray;

	ray.r = 0.0;
	ray.i = cub3d->player.right.i * h;
	ray.j = cub3d->player.right.j * h;
	ray.k = 0.0;
	ray.i += cub3d->player.pos.i - cub3d->player.cam.i;
	ray.j += cub3d->player.pos.j - cub3d->player.cam.j;
	return (intersect(cub3d, ray, tx_h, dist));
}

uint32_t	pixel_color(t_cub3d *cub3d, double tx_h, double tx_v, int side)
{
	int		x;
	int		y;

	x = (int) (tx_h * cub3d->textures[side]->width);
	y = (int) (tx_v * cub3d->textures[side]->height);
	return (((uint32_t *)cub3d->textures[side]->pixels)
		[y * cub3d->textures[side]->width + x]);
}

void	drawline(t_cub3d *cub3d, int h, double tx_h, double dist, int side)
{
	int			v;
	double		tx_v;
	double		lim;

	lim = 0.5 / dist * sqrt(CAM_DIST * CAM_DIST + h * h); //0.5 * CUBE_EDGE
//	printf("[dist, lim: %f, %f] ", dist, lim);
	v = -1;
	while(++v < (HEIGHT + 1) / 2 - lim)
	{
		((uint32_t *)cub3d->img->pixels)
		[v * WIDTH + h + WIDTH / 2] = cub3d->colors.ceiling_color;
		((uint32_t *)cub3d->img->pixels)
		[(HEIGHT - 1 - v) * WIDTH + h + WIDTH / 2] = cub3d->colors.floor_color;
	}
	while(++v < (HEIGHT + 1) / 2)
	{
		tx_v = (2 * v - HEIGHT) / (4 * lim) + 0.5;
		((uint32_t *)cub3d->img->pixels)
		[v * WIDTH + h + WIDTH / 2] = pixel_color(cub3d, tx_h, tx_v, side);
		((uint32_t *)cub3d->img->pixels)
		[(HEIGHT - 1 - v) * WIDTH + h + WIDTH / 2] = pixel_color(cub3d, tx_h, 1 - tx_v, side);
	}
}

void	render(t_cub3d *cub3d)
{
	int		h;
	double	dist;
	double	tx_h;
	int		side;

	h = -WIDTH / 2 - 1;
	while(++h < WIDTH / 2)
	{
		side = raycast(cub3d, h, &tx_h, &dist);
		drawline(cub3d, h, tx_h, dist, side);
	}
	cub3d->frames_shown++;
	printf("frames_shown: %d\n", cub3d->frames_shown);
}