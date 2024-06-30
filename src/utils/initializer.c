/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:47:24 by yunlovex          #+#    #+#             */
/*   Updated: 2024/06/30 16:33:57 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static void	event_init(t_fractol *fractol)
{
	mlx_hook(fractol->mlx_win, KEYPRESS, 1L << 0, key_handler, fractol);
	mlx_hook(fractol->mlx_win, DESTROYNOTIFY, 1L << 17, close_handler, fractol);
	mlx_hook(fractol->mlx_win, BUTTONPRESS, 1L << 2, mouse_handler, fractol);
	mlx_hook(fractol->mlx_win, BUTTONRELEASE, 1L << 3,
		mouse__release_handler, fractol);
	mlx_hook(fractol->mlx_win, MOTIONNOTIFY, 1L << 8, julia_track, fractol);
	mlx_hook(fractol->win_prnt, KEYPRESS, 1L << 0, key_handler, fractol);
	mlx_hook(fractol->win_prnt, DESTROYNOTIFY, 1L << 17, close_handler,
		fractol);
}*/

static void	init_graph(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		cub3d_error("mlx_init", 1);
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	cub3d->img->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img->img || !cub3d->win)
	{
		if (cub3d->img->img)
			mlx_destroy_image(cub3d->mlx, cub3d->img->img);
		if (cub3d->win)
			mlx_destroy_window(cub3d->mlx, cub3d->win);
		free(cub3d->mlx);
		cub3d_error("image/window", 1);
	}
	cub3d->img->addr = mlx_get_data_addr(cub3d->img->img,
			&cub3d->img->bits_per_pixel, &cub3d->img->line_length,
			&cub3d->img->endian);
	if (!cub3d->img->addr)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->img->img);
		mlx_destroy_window(cub3d->mlx, cub3d->win);
		free(cub3d->mlx);
		cub3d_error("mlx_get_data_addr", 1);
	}
}

void	init(t_cub3d *cub3d)
{
	init_graph(cub3d);
	//init_events(cub3d);
}


void	deinit(t_cub3d *cub3d)
{
	
}
