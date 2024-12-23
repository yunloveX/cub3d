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

int	collision(t_cub3d *cub3d)
{
	t_quaternion	tmp1;
	int				x1;
	int				y1;
	t_quaternion	tmp2;
	int				x2;
	int				y2;

	tmp1 = q_add(cub3d->player.pos, q_scale(cub3d->player.right, -WIDTH / 2));
	x1 = (int) tmp1.i;
	y1 = (int) -tmp1.j;
	if (cub3d->map.grid[y1][x1] == '1')
		return (1);
	tmp2 = q_add(cub3d->player.pos, q_scale(cub3d->player.right, WIDTH / 2));
	x2 = (int) tmp2.i;
	y2 = (int) -tmp2.j;
	if (cub3d->map.grid[y2][x2] == '1')
		return (1);
	if (x1 == x2 || y1 == y2)
		return (0);
	if (cub3d->map.grid[y1][x2] == '1' || cub3d->map.grid[y2][x1] == '1')
		return (1);
	return (0);
}

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
	locate_cam(cub3d);
	if (collision(cub3d))
		rotate_horizontal(cub3d, -xpos);
}

void	move(t_cub3d *cub3d, double step)
{
/*	cub3d->player_old = cub3d->player;*/
	cub3d->player.pos = q_add(cub3d->player.pos, q_scale(q_sub(cub3d->player.pos,
		cub3d->player.cam), step));
	locate_cam(cub3d);
	if (collision(cub3d))
		move(cub3d, -step);
}

void	key_hook_function(mlx_key_data_t key_data, void *param)
{
    t_cub3d	*cub3d;
	int	i;

	if (key_data.action == MLX_RELEASE)
		return ;
	cub3d = (t_cub3d *)param;
/*	if (key_data.key == MLX_KEY_Y)
	{
			cub3d->img->enabled ^= true;
			printf("img enabled: %d\n", cub3d->img->enabled);
	}*/
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
	else if (key_data.key == MLX_KEY_ESCAPE)
		mlx_terminate(cub3d->mlx);
	else
		return ;
	render(cub3d);
}

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

void	mouse_hook_function(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
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


void    loop_hook_function(void *param)
{
    t_cub3d	*cub3d;
	int32_t	xpos;
	int32_t	ypos;

    cub3d = (t_cub3d *)param;
	if (!cub3d->mouse_down)
		return ;
	mlx_get_mouse_pos(cub3d->mlx, &xpos, &ypos);
//	printf("mouse xpos: %d, ypos: %d\n", xpos, ypos);
	if (cub3d->mouse_down == 1)
	{
		xpos -= cub3d->old_x;
		ypos -= cub3d->old_y;
	}
	else
	{
		xpos -= WIDTH / 2;
		if (abs(xpos) > 50)
			xpos = xpos / abs(xpos) * 50;
		ypos -= HEIGHT / 2;
		if (abs(ypos) > 50)
			ypos = ypos / abs(ypos) * 50;
		xpos = -xpos / 5;
		ypos = -ypos / 10;

	}
	if (xpos)
		rotate_horizontal(cub3d, (double)xpos / 5.0);
	if (ypos)
		cub3d->player.pos = q_add(cub3d->player.pos, q_scale(q_sub(cub3d->player.pos,
			cub3d->player.cam), (double)ypos / 100.0));
	locate_cam(cub3d);
	cub3d->old_x += xpos;
	cub3d->old_y += ypos;
	render(cub3d);
}