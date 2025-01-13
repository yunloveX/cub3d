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
	ray.i += cub3d->player.pos.i; // - cub3d->player.cam.i;
	ray.j += cub3d->player.pos.j; // - cub3d->player.cam.j;
	if (map(cub3d,  ray.i, -ray.j) == '1')
	{
		*dist = 0;
		return (-1);
	}
	ray.i -= cub3d->player.cam.i;
	ray.j -= cub3d->player.cam.j;
	return (intersect(cub3d, ray, tx_h, dist));
}

uint8_t	darkness(int y, int height)
{
	uint8_t		dark_y;

	if (y < 10)
		dark_y = 28 * y;
	else if (height - y < 10)
		dark_y = 28 * (height - y);
	else
		dark_y = 255;
	return (dark_y);
}

void	light_part(uint32_t *color, uint8_t fraction)
{
	uint32_t	tmp;

	tmp = (*color & 0xff00) >> 8;
	tmp *= fraction;
	tmp = (tmp + (tmp >> 8) + 0x80) >> 8;
	*color = (*color & 0xffff00ff) | (tmp << 8);
	tmp = (*color & 0xff0000) >> 16;
	tmp *= fraction;
	tmp = (tmp + (tmp >> 8) + 0x80) >> 8;
	*color = (*color & 0xff00ffff) | (tmp << 16);
	tmp = (*color & 0xff000000) >> 24;
	tmp *= fraction;
	tmp = (tmp + (tmp >> 8) + 0x80) >> 8;
	*color = (*color & 0x00ffffff) | (tmp << 24);
}

uint32_t	pixel_color(t_cub3d *cub3d, double tx_h, double tx_v, int side)
{
	int			x;
	int			y;
	uint32_t	color;

	x = (int) (tx_h * cub3d->textures[side]->width);
	y = (int) (tx_v * cub3d->textures[side]->height);
	color = color_from_mem((cub3d->textures[side]->pixels)
		+ 4 * (y * cub3d->textures[side]->width + x));
	light_part(&color, darkness(y, cub3d->textures[side]->height));
	return (color);
}

void	drawline(t_cub3d *cub3d, int h, double tx_h, double dist, int side)
{
	int			v;
	double		tx_v;
	double		lim;

	lim = 0.5 / dist * sqrt(CAM_DIST * CAM_DIST + h * h); //0.5 * CUBE_EDGE
//	printf("[dist, lim: %f, %f] ", dist, lim);
	v = -1;
	while(++v <= (HEIGHT + 1) / 2 - lim)
	{
		mlx_put_pixel(cub3d->img, h + WIDTH / 2, v, cub3d->colors.ceiling_color);
		mlx_put_pixel(cub3d->img, h + WIDTH / 2, HEIGHT - 1 - v, cub3d->colors.floor_color);
	}
	v--;
	while(++v < (HEIGHT + 1) / 2)
	{
		tx_v = (2 * v - HEIGHT) / (4 * lim) + 0.5;
/*		((uint32_t *)cub3d->img->pixels)
		[v * WIDTH + h + WIDTH / 2] = pixel_color(cub3d, tx_h, tx_v, side);
		((uint32_t *)cub3d->img->pixels)
		[(HEIGHT - 1 - v) * WIDTH + h + WIDTH / 2] = pixel_color(cub3d, tx_h, 1 - tx_v, side);*/
		mlx_put_pixel(cub3d->img, h + WIDTH / 2, v, pixel_color(cub3d, tx_h, tx_v, side));
		mlx_put_pixel(cub3d->img, h + WIDTH / 2, HEIGHT - 1 - v, pixel_color(cub3d, tx_h, 1 - tx_v, side));
	}
}

void transparent_pixel(uint8_t *pixel, uint32_t color)
{
	int		alpha;
	uint32_t	tmp;

	alpha = color & 0xff;
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
/*
void	mix_colors(int color, uint32_t *pixel)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	r = (color & 0xff0000) >> 16;
	g = (color & 0xff00) >> 8;
	b = color & 0xff;
	a = (color & 0xff000000) >> 24;
	r = (r * a + ((*pixel & 0xff0000) >> 16) * (255 - a)) / 255;
	g = (g * a + ((*pixel & 0xff00) >> 8) * (255 - a)) / 255;
	b = (b * a + (*pixel & 0xff) * (255 - a)) / 255;
	*pixel = (r << 16) | (g << 8) | b;
}
*/

void	put_map_dot(t_cub3d *cub3d, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
//			mlx_put_pixel(cub3d->img, x * 5 + i, y * 5 + j, color);
//			mlx_draw_pixel(cub3d->img->pixels +
			transparent_pixel(cub3d->img->pixels +
			4 * ((y * 5 + j) * WIDTH + x * 5 + i), color);
			j++;
		}
		i++;
//		mlx_put_pixel(cub3d->img, x * 5, y * 5, color);
	}
}

void	show_map(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		color;

	y = -2;
	while (++y < cub3d->map.height + 1)
	{
		x = -2;
		while (++x < cub3d->map.width + 1)
		{
			if (x == (int) cub3d->player.pos.i && y == (int) -cub3d->player.pos.j)
				color = 0xff0000ff;
			else if (x < 0 || x == cub3d->map.width|| y < 0
				|| y == cub3d->map.height || cub3d->map.grid[y][x] != '1')
				color = 0xffffff40;
			else
				color = 0x000000ff;
			put_map_dot(cub3d, x + 1, y + 1, color);
		}
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
		if (side < 0)
			break;
		drawline(cub3d, h, tx_h, dist, side);
	}
	if (side < 0)
	{
		player_equal(&cub3d->player, &cub3d->player_old);
		render(cub3d);
		return ;
	}
	player_equal(&cub3d->player_old, &cub3d->player);
	show_map(cub3d);
	mlx_put_pixel(cub3d->img, WIDTH / 2, HEIGHT / 2, 0xff0000ff);
	cub3d->frames_shown++;
//	printf("frames_shown: %d\n", cub3d->frames_shown);
}