/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallUtils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:13:55 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 13:00:14 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

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

void	locate_door(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->map.door_states[y][x] == 0)
	{
		cub3d->temp_door_x = x;
		cub3d->temp_door_y = y;
	}
}

int	wall_north_south(t_cub3d *cub3d, t_quaternion progress, float delta_j,
	double *tx_h)
{
	int	x;
	int	y;

	x = (int) floor(progress.i);
	y = (int) floor(0.5 - progress.j);
	locate_door(cub3d, x, y);
	if (delta_j < 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = ceil(progress.i) - progress.i;
		if (cub3d->map.door_states[y][x] == 1)
			return (cub3d->temp_door_x = x, cub3d->temp_door_y = y, 4);
		return (0);
	}
	y--;
	locate_door(cub3d, x, y);
	if (delta_j > 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = progress.i - floor(progress.i);
		if (cub3d->map.door_states[y][x] == 1)
			return (cub3d->temp_door_x = x, cub3d->temp_door_y = y, 4);
		return (2);
	}
	return (-1);
}

int	wall_east_west(t_cub3d *cub3d, t_quaternion progress, float delta_i,
	double *tx_h)
{
	int	x;
	int	y;

	x = (int) floor(progress.i - 0.5);
	y = (int) floor(-progress.j);
	locate_door(cub3d, x, y);
	if (delta_i < 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = ceil(progress.j) - progress.j;
		if (cub3d->map.door_states[y][x] == 1)
			return (cub3d->temp_door_x = x, cub3d->temp_door_y = y, 4);
		return (3);
	}
	x++;
	locate_door(cub3d, x, y);
	if (delta_i > 0 && map(cub3d, x, y) == '1')
	{
		*tx_h = progress.j - floor(progress.j);
		if (cub3d->map.door_states[y][x] == 1)
			return (cub3d->temp_door_x = x, cub3d->temp_door_y = y, 4);
		return (1);
	}
	return (-1);
}

int	meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray,
	double *tx_h)
{
	if (at_limit(progress.i))
		return (wall_east_west(cub3d, progress, ray.i, tx_h));
	if (at_limit(progress.j))
		return (wall_north_south(cub3d, progress, ray.j, tx_h));
	return (-1);
}
