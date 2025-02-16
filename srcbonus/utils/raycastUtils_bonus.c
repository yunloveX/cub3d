/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastUtils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:16:52 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 13:00:14 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

char	map(t_cub3d *cub3d, int x, int y)
{
	if (x < 0 || y < 0 || x >= cub3d->map.width || y >= cub3d->map.height)
		return ('1');
	if (cub3d->map.grid[y][x] == 'D')
	{
		if (cub3d->map.door_states[y][x] == 0)
			return ('0');
		else
			return ('1');
	}
	return (cub3d->map.grid[y][x]);
}

static void	update_gap(t_quaternion *gap, t_quaternion dir, double min)
{
	gap->i = gap->i - dir.i * min;
	if (gap->i * dir.i <= 0 && dir.i != 0)
		gap->i = dir.i / fabs(dir.i);
	gap->j = gap->j - dir.j * min;
	if (gap->j * dir.j <= 0 && dir.j != 0)
		gap->j = dir.j / fabs(dir.j);
}

double	min_jump(t_cub3d *cub3d, t_quaternion *gap, t_quaternion dir)
{
	double	min;

	min = 0;
	if (fabs(dir.i) > TOLERANCE)
		cub3d->jumps[0] = gap->i / dir.i;
	else
		cub3d->jumps[0] = FAR;
	if (fabs(dir.j) > TOLERANCE)
		cub3d->jumps[1] = gap->j / dir.j;
	else
		cub3d->jumps[1] = FAR;
	if (cub3d->jumps[0] > 0 && cub3d->jumps[0] < FAR
		&& cub3d->jumps[0] <= cub3d->jumps[1])
		min = (cub3d->jumps[0]);
	else
		min = (cub3d->jumps[1]);
	if (min)
		update_gap(gap, dir, min);
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
			return (0);
		*dist += d_jump;
		progress = q_add(cub3d->player.cam, q_scale(ray, *dist));
		ret = meet_wall(cub3d, progress, ray, tx_h);
	}
	return (ret);
}

int	raycast(t_cub3d *cub3d, int h, double *tx_h, double *dist)
{
	t_quaternion	ray;

	ray.r = 0.0;
	ray.i = cub3d->player.right.i * h;
	ray.j = cub3d->player.right.j * h;
	ray.k = 0.0;
	ray.i += cub3d->player.pos.i;
	ray.j += cub3d->player.pos.j;
	if (map(cub3d, ray.i, -ray.j) == '1')
	{
		*dist = 0;
		return (-1);
	}
	ray.i -= cub3d->player.cam.i;
	ray.j -= cub3d->player.cam.j;
	return (intersect(cub3d, ray, tx_h, dist));
}
