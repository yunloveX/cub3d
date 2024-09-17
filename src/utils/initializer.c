/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:47:24 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/02 18:44:56 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_events(t_cub3d *cub3d)
{
	mlx_cursor_hook(cub3d->mlx, cursor_hook_function, cub3d);
}

static void	init_cam(t_cub3d *cub3d)
{
}

static void	init_graph(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!cub3d->mlx)
		cub3d_error("mlx_init", 1);
	//cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img)
	{
		free(cub3d->mlx);
		cub3d_error("image", 1);
	}
	mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);
}

void	init(t_cub3d *cub3d)
{
	init_graph(cub3d);
	init_events(cub3d);
}
