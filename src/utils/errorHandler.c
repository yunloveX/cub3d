/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorHandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:21:02 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/13 09:22:39 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	cub3d_error(char *message, int error, t_cub3d *cub3d)
{
	if (cub3d->mlx)
		mlx_terminate(cub3d->mlx);
	printf("%s", message);
	exit(error);
}
