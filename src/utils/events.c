/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:49:45 by yunlovex          #+#    #+#             */
/*   Updated: 2024/06/20 14:53:45 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	render(double xpos, double ypos, t_cub3d *cub3d)
{
	uint32_t	h;
	uint32_t	v;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	h = 0;
	v = 0;
	while (v < HEIGHT)
	{
		g = 256 * ((v + (int) ypos * 2) % HEIGHT) / HEIGHT;
		h = 0;
		while (h < WIDTH)
		{
			r = 256 * ((h + (int) xpos * 2) % WIDTH) / WIDTH;
			b = 255 - r / 2 - g / 2;
			mlx_put_pixel(cub3d->img, h, v, color_rgba(r, g, b, 255));
			h++;
		}
		v++;
	}
	//TODO render
}*/

void	rotate_horizontal(t_cub3d *cub3d, double xpos)
{
	t_quaternion	rot;
	double			costh;
	double			sinth;

/*	cub3d->player_old = cub3d->player;*/
	sinth = xpos / 1000;
	costh = sqrt(1.0 - sinth * sinth);
	rot.r = costh;
	rot.i = 0.0;
	rot.j = 0.0;
	rot.k = sinth;
	cub3d->player.right = q_rotate(cub3d->player.right, rot);
}

void	move(t_cub3d *cub3d, double step)
{
/*	cub3d->player_old = cub3d->player;*/
	cub3d->player.pos = q_add(cub3d->player.pos, q_scale(q_sub(cub3d->player.pos,
		cub3d->player.cam), step));
}
/*
void	no_collision(t_cub3d *cub3d)
{
	t_quaternion	tmp;

	tmp = q_add(cub3d->player.pos, q_scale(cub3d->player.right, -WIDTH / 2));
	if (cub3d->map.grid[(int) -tmp.j][(int) tmp.i] == '1')
	{
		cub3d->player.pos = q_add(cub3d->player.pos, q_scale(cub3d->player.right, WIDTH / 20));
		no_collision(cub3d);
	}
	tmp = q_add(cub3d->player.pos, q_scale(cub3d->player.right, WIDTH / 2));
	if (cub3d->map.grid[(int) -tmp.j][(int) tmp.i] == '1')
	{
		cub3d->player.pos = q_add(cub3d->player.pos, q_scale(cub3d->player.right, -WIDTH / 20));
		no_collision(cub3d);
	}
}*/

void	key_hook_function(mlx_key_data_t key_data, void *param)
{
    t_cub3d	*cub3d;

	if (key_data.action == MLX_RELEASE)
		return ;
	cub3d = (t_cub3d *)param;
	if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
		rotate_horizontal(cub3d, 10.0);
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
		rotate_horizontal(cub3d, -10.0);
	else if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		move(cub3d, 0.2);
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		move(cub3d, -0.2);
	else if (key_data.key == MLX_KEY_ESCAPE)
		mlx_terminate(cub3d->mlx);
	else
		return ;
/*	no_collision(cub3d);*/
	locate_cam(cub3d);
	printf("pos: %f, %f, %f\n", cub3d->player.pos.i, cub3d->player.pos.j, cub3d->player.pos.k);
	printf("cam: %f, %f, %f\n", cub3d->player.cam.i, cub3d->player.cam.j, cub3d->player.cam.k);
	render(cub3d);
}
/*
void    loop_hook_function(void *param)
{
    t_cub3d	*cub3d;
	int	xpos;
	int	ypos;

//	printf("scrolling xpos: %f, ypos: %f\n", xpos, ypos);
    cub3d = (t_cub3d *)param;
	if (!mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_LEFT))
		return ;
	mlx_get_mouse_pos(cub3d->mlx, &xpos, &ypos);
	if (xpos != WIDTH / 2)
		rotate_horizontal(cub3d, -((double)xpos - (double)WIDTH / 2.0) / 10.0);
	if (ypos != HEIGHT / 2)
		cub3d->player.pos = q_add(cub3d->player.pos, q_scale(q_sub(cub3d->player.pos,
			cub3d->player.cam), -((double)ypos - (double)HEIGHT / 2.0) / 400.0));
	locate_cam(cub3d);
	render(cub3d);
}*/