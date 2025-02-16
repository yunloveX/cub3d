/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:13:55 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 17:14:29 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

int	wall_north_south(t_cub3d *cub3d, t_quaternion progress, float delta_j,
	double *tx_h)
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

int	wall_east_west(t_cub3d *cub3d, t_quaternion progress, float delta_i,
	double *tx_h)
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

int	meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray,
	double *tx_h)
{
	if (at_limit(progress.i))
		return (wall_east_west(cub3d, progress, ray.i, tx_h));
	if (at_limit(progress.j))
		return (wall_north_south(cub3d, progress, ray.j, tx_h));
	return (-1);
}
