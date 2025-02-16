/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windowClose_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:02:40 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 12:56:09 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_bonus.h"

void	close_hook_function(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *) param;
	mlx_terminate(cub3d->mlx);
	exit(0);
}
