/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:20:44 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 13:00:14 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

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

void	player_equal(t_player *player_to, t_player *player_from)
{
	player_to->pos = player_from->pos;
	player_to->right = player_from->right;
	player_to->down = player_from->down;
	player_to->cam = player_from->cam;
}
