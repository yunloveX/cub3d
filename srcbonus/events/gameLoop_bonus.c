/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameLoop_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:54:47 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 12:55:44 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_bonus.h"

static void	handle_mouse_movement(t_cub3d *cub3d, int32_t *xpos, int32_t *ypos)
{
	mlx_get_mouse_pos(cub3d->mlx, xpos, ypos);
	if (cub3d->mouse_down == 1)
	{
		*xpos -= cub3d->old_x;
		*ypos -= cub3d->old_y;
	}
	else
	{
		*xpos -= WIDTH / 2;
		*ypos -= HEIGHT / 2;
		*xpos = -(*xpos);
		*ypos = -(*ypos);
	}
}

static void	update_player_position(t_cub3d *cub3d, int32_t xpos, int32_t ypos)
{
	if (xpos)
		rotate_horizontal(cub3d, (double)xpos / 5.0);
	if (ypos)
		cub3d->player.pos = q_add(cub3d->player.pos,
				q_scale(q_sub(cub3d->player.pos, cub3d->player.cam),
					(double)ypos / 100.0));
	locate_cam(cub3d);
	cub3d->old_x += xpos;
	cub3d->old_y += ypos;
}

void	handle_hand_animation(t_cub3d *cub3d)
{
	if (cub3d->hand_playing)
	{
		cub3d->slow_count++;
		if (cub3d->slow_count % SLOW_SPRITE == 0)
		{
			cub3d->slow_count = 0;
			cub3d->hand_frame = cub3d->hand_frame->next;
			render(cub3d);
			if (cub3d->hand_frame == NULL)
			{
				cub3d->hand_frame = *(cub3d->hand_texture);
				cub3d->hand_playing = 0;
			}
			else
				sprite(cub3d);
		}
	}
	sprite(cub3d);
}

void	loop_hook_function(void *param)
{
	t_cub3d	*cub3d;
	int32_t	xpos;
	int32_t	ypos;

	cub3d = (t_cub3d *) param;
	handle_hand_animation(cub3d);
	if (!cub3d->mouse_down)
		return ;
	handle_mouse_movement(cub3d, &xpos, &ypos);
	update_player_position(cub3d, xpos, ypos);
	render(cub3d);
	sprite(cub3d);
}
