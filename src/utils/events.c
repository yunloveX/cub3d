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

	sinth = xpos / 1000;
	costh = sqrt(1.0 - sinth * sinth);
	rot.r = costh;
	rot.i = 0.0;
	rot.j = 0.0;
	rot.k = sinth;
	cub3d->player.right = q_rotate(cub3d->player.right, rot);
}

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
}