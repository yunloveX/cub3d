/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:54:16 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/12 10:40:10 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	rotate_horizontal(t_cub3d *cub3d, double xpos)
{
	t_quaternion	rot;
	double			costh;
	double			sinth;

	sinth = xpos / 1000;
	costh = sqrt(1.0 - sinth * sinth);
	rot.r = costh;
	rot.i = 0.0;
	rot.j = 0.0;
	rot.k = sinth;
	cub3d->player.right = q_rotate(cub3d->player.right, rot);
	locate_cam(cub3d);
}

void	move(t_cub3d *cub3d, double step)
{
	cub3d->player.pos = q_add(cub3d->player.pos,
			q_scale(q_sub(cub3d->player.pos, cub3d->player.cam), step));
	locate_cam(cub3d);
}
