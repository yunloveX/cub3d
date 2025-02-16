/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboardInput_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:52:37 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 12:56:09 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_bonus.h"

void	toggle_door(t_cub3d *cub3d, int x, int y)
{
	if (x >= 0 && y >= 0 && x < cub3d->map.width && y < cub3d->map.height)
	{
		if (cub3d->map.grid[y][x] == 'D')
		{
			cub3d->map.door_states[y][x] ^= 1;
			((uint32_t *)cub3d->img_map->pixels)
			[(y + 1) * cub3d->img_map->width + (x + 1)] ^= 0x00c000c0;
		}
	}
}

// Call this when player presses 'E'
void	check_door_interaction(t_cub3d *cub3d)
{
	double	tx_h;
	double	dist;
	int		side;

	cub3d->temp_door_x = -1;
	cub3d->temp_door_y = -1;
	side = raycast(cub3d, 0, &tx_h, &dist);
	if (side == 4 && cub3d->temp_door_x != -1 && cub3d->temp_door_y != -1)
		toggle_door(cub3d, cub3d->temp_door_x, cub3d->temp_door_y);
	else
	{
		side = raycast(cub3d, 1, &tx_h, &dist);
		if (side != 4 && cub3d->temp_door_x != -1 && cub3d->temp_door_y != -1
			&& (abs((int)(cub3d->player.pos.i - cub3d->temp_door_x - 0.5)) > 0.5
			|| abs((int)(-cub3d->player.pos.j - cub3d->temp_door_y - 0.5))
				> 0.5))
			toggle_door(cub3d, cub3d->temp_door_x, cub3d->temp_door_y);
	}
}

void	special_key_function(mlx_key_data_t key_data, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (key_data.key == MLX_KEY_R)
	{
		cub3d->hand_frame = *(cub3d->hand_texture);
		cub3d->hand_playing ^= 1;
	}
	else if (key_data.key == MLX_KEY_ESCAPE)
		close_hook_function(cub3d);
	else if (key_data.key == MLX_KEY_E && key_data.action == MLX_PRESS)
		check_door_interaction(cub3d);
	else
		return ;
}

void	key_hook_function(mlx_key_data_t key_data, void *param)
{
	t_cub3d	*cub3d;
	int		i;

	if (key_data.action == MLX_RELEASE)
		return ;
	cub3d = (t_cub3d *)param;
	if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
	{
		i = -1;
		while (++i < 10)
			rotate_horizontal(cub3d, 1.0);
	}
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
	{
		i = -1;
		while (++i < 10)
			rotate_horizontal(cub3d, -1.0);
	}
	else if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		move(cub3d, 0.2);
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		move(cub3d, -0.2);
	else
		special_key_function(key_data, cub3d);
	render(cub3d);
}
