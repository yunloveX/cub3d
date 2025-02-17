/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsRenderer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:16:50 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/17 08:37:09 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_cub3d *cub3d)
{
	int		h;
	int		side;
	double	dist;
	double	tx_h;

	h = -WIDTH / 2 - 1;
	while (++h < WIDTH / 2)
	{
		side = raycast(cub3d, h, &tx_h, &dist);
		if (side < 0)
			break ;
		drawline(cub3d, tx_h, dist, (int [2]){side, h});
	}
	if (side < 0)
	{
		player_equal(&cub3d->player, &cub3d->player_old);
		render(cub3d);
		return ;
	}
	player_equal(&cub3d->player_old, &cub3d->player);
}
