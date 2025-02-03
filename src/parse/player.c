/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:52:08 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/03 12:17:37 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_equal(t_player *player_to, t_player *player_from)
{
	player_to->pos = player_from->pos;
	player_to->right = player_from->right;
	player_to->down = player_from->down;
	player_to->cam = player_from->cam;
}

static void	locate_player(t_cub3d *cub3d, int y, int x)
{
	char	c;

	cub3d->player.pos.i = 0.51 + x;
	cub3d->player.pos.j = -0.51 - y;
	cub3d->player.pos.k = 0.5;
	q_zero(&cub3d->player.down);
	cub3d->player.down.k = -1.0 / CUBE_EDGE;
	q_zero(&cub3d->player.right);
	c = cub3d->map.grid[y][x];
	if (c == 'N')
		cub3d->player.right.i = 1.0 / CUBE_EDGE;
	if (c == 'S')
		cub3d->player.right.i = -1.0 / CUBE_EDGE;
	if (c == 'E')
		cub3d->player.right.j = -1.0 / CUBE_EDGE;
	if (c == 'W')
		cub3d->player.right.j = 1.0 / CUBE_EDGE;
	locate_cam(cub3d);
	player_equal(&cub3d->player_old, &cub3d->player);
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	parse_player(t_cub3d *cub3d)
{
	int		y;
	int		x;

	y = 0;
	q_zero(&cub3d->player.pos);
	while (y < cub3d->map.height)
	{
		x = 0;
		while (cub3d->map.grid[y][x])
		{
			if (is_player(cub3d->map.grid[y][x]))
			{
				if (cub3d->player.pos.k)
					cub3d_error("Error\nMultiple players found", 1);
				locate_player(cub3d, y, x);
			}
			x++;
		}
		y++;
	}
	if (!cub3d->player.pos.k)
		cub3d_error("Error\nNo player found", 1);
}
