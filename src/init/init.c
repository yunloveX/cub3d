/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:47:24 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/03 14:30:13 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_events(t_cub3d *cub3d)
{
	mlx_key_hook(cub3d->mlx, key_hook_function, cub3d);
	mlx_loop_hook(cub3d->mlx, loop_hook_function, cub3d);
	mlx_scroll_hook(cub3d->mlx, scroll_hook_function, cub3d);
	mlx_mouse_hook(cub3d->mlx, mouse_hook_function, cub3d);
}

static void init_data(t_cub3d *cub3d)
{
	cub3d->mouse_down = false;
    cub3d->textures[0] = NULL;
    cub3d->textures[2] = NULL;
    cub3d->textures[1] = NULL;
    cub3d->textures[3] = NULL;
    cub3d->textures[4] = NULL;
    cub3d->textures[5] = NULL;
    cub3d->textures[6] = NULL;
    cub3d->textures[7] = NULL;
    cub3d->map.grid = NULL;
	cub3d->map.door_states = NULL;
    cub3d->map.width = 0;
    cub3d->map.height = 0;
}

static void	init_graph(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!cub3d->mlx)
		cub3d_error("mlx_init", 1);
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img)
	{
		free(cub3d->mlx);
		cub3d_error("image", 1);
	}
	cub3d->frames_shown = 0;
	mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);
}

void	init(t_cub3d *cub3d)
{
	init_data(cub3d);
	init_graph(cub3d);
	init_events(cub3d);
}
