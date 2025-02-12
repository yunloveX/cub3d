/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:02:40 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/12 09:31:07 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	close_hook_function(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *) param;
	mlx_terminate(cub3d->mlx);
	ft_lstclear(&cub3d->hand_frame, NULL);
	free(cub3d->hand_texture);
	double_free(cub3d->map.grid);
	cub3d->map.grid = NULL;
	double_free(cub3d->map.door_states);
	cub3d->map.door_states = NULL;
}