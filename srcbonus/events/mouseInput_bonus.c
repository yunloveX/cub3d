/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseInput_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:53:53 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 12:56:09 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_bonus.h"

void	scroll_hook_function(double xdelta, double ydelta, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (ydelta)
		move(cub3d, ydelta / 10.0);
	if (xdelta)
		rotate_horizontal(cub3d, xdelta);
	render(cub3d);
}

void	mouse_hook_function(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	mods = 0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS && !mods)
	{
		cub3d->mouse_down |= 1;
		mlx_get_mouse_pos(cub3d->mlx, &cub3d->old_x, &cub3d->old_y);
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		cub3d->mouse_down &= 0xfe;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
	{
		cub3d->mouse_down |= 2;
		mlx_get_mouse_pos(cub3d->mlx, &cub3d->old_x, &cub3d->old_y);
	}
	else if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
		cub3d->mouse_down &= 0xfd;
}
