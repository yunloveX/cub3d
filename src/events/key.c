/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:52:37 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/03 12:06:41 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void toggle_door(t_cub3d *cub3d, int x, int y) {
    if (x >= 0 && y >= 0 && x < cub3d->map.width && y < cub3d->map.height) {
        if (cub3d->map.grid[y][x] == 'D') {
            cub3d->map.door_states[y][x] ^= 1; // Toggle state
        }
    }
}

// Call this when player presses 'E'
void check_door_interaction(t_cub3d *cub3d) {
    int px = (int)cub3d->player.pos.i;
    int py = (int)(-cub3d->player.pos.j);
    // Check adjacent cells
    toggle_door(cub3d, px + 1, py);
    toggle_door(cub3d, px - 1, py);
    toggle_door(cub3d, px, py + 1);
    toggle_door(cub3d, px, py - 1);
}

void	key_hook_function(mlx_key_data_t key_data, void *param)
{
    t_cub3d	*cub3d;
	int	i;

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
	else if (key_data.key == MLX_KEY_E && key_data.action == MLX_PRESS)
        check_door_interaction(cub3d);
	else if (key_data.key == MLX_KEY_ESCAPE)
		mlx_terminate(cub3d->mlx);
	else
		return ;
	render(cub3d);
}