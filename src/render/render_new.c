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
	if (d_abs(dir.k) > TOLERANCE)
		cub3d->jumps[2] = gap->k / dir.k;
	else
		cub3d->jumps[2] = FAR;
//	printf("jump_i: %f\n", jump_i);
//	printf("jump_j: %f\n", jump_j);
//	printf("jump_k: %f\n", jump_k);
	if (cub3d->jumps[0] > 0 && cub3d->jumps[0] < FAR
		&& cub3d->jumps[0] <= cub3d->jumps[1] && cub3d->jumps[0] <= cub3d->jumps[2])
		min = (cub3d->jumps[0]);
	if (cub3d->jumps[1] > 0 && cub3d->jumps[1] < FAR
		&& cub3d->jumps[1] <= cub3d->jumps[0] && cub3d->jumps[1] <= cub3d->jumps[2])
		min = (cub3d->jumps[1]);
	if (cub3d->jumps[2] > 0 && cub3d->jumps[2] < FAR
		&& cub3d->jumps[2] <= cub3d->jumps[0] && cub3d->jumps[2] <= cub3d->jumps[1])
		min = (cub3d->jumps[2]);
	if (min)
	{
		gap->i = gap->i - dir.i * min;
		if (gap->i * dir.i <= 0)
			gap->i = dir.i / d_abs(dir.i);
		gap->j = gap->j - dir.j * min;
		if (gap->j * dir.j <= 0)
			gap->j = dir.j / d_abs(dir.j);
		gap->k = gap->k - dir.k * min;
		if (gap->k * dir.k <= 0)
			gap->k = dir.k / d_abs(dir.k);
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
			return (0xFF0000FF); //RED
		*dist += d_jump;
//		printf("jump: %f\n", jump);
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

void	drawline(t_cub3d *cub3d, int h, int tx_h, int dist, int side)
{
	int			v;
	int			tx_v;
	uint32_t	color;
	double		lim;

	lim = h - WIDTH / 2;
	lim = 0.5 / dist * sqrt(CAM_DIST * CAM_DIST + lim * lim);
	v = -1;
	while(++v < HEIGHT)
	{
		if (v < HEIGHT / 2 - lim)
			color = cub3d->colors.ceiling_color;
		else if (v > HEIGHT / 2 + lim)
			color = cub3d->colors.floor_color;
		else
			color = pixel_color(cub3d, tx_h, tx_v, side);
	}
}
void	render(t_cub3d *cub3d)
{
	int		h;
	double	dist;
	double	tx_h;
	int		side;

	h = -1;
	while(++h < WIDTH)
	{
		side = raycast(cub3d, h, &tx_h, &dist);
		drawline(cub3d, h, tx_h, dist, side);
	}
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