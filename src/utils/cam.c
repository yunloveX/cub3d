/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:20:44 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/03 12:21:19 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	locate_pos(t_cub3d *cub3d)
{
	cub3d->player.pos = q_mul(cub3d->player.right, cub3d->player.down);
	cub3d->player.pos = q_add(cub3d->player.cam,
		q_scale(cub3d->player.pos, CUBE_EDGE * CAM_DIST));
}

void	locate_cam(t_cub3d *cub3d)
{
	cub3d->player.cam = q_mul(cub3d->player.right, cub3d->player.down);
	cub3d->player.cam = q_add(cub3d->player.pos,
		q_scale(cub3d->player.cam, -CUBE_EDGE * CAM_DIST));
}