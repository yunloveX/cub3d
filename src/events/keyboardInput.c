/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboardInput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:52:37 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/17 08:05:45 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	special_key_function(mlx_key_data_t key_data, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (key_data.key == MLX_KEY_ESCAPE)
		close_hook_function(cub3d);
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
