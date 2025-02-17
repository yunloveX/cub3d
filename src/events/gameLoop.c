/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameLoop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:54:47 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/17 08:08:01 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	loop_hook_function(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *) param;
	render(cub3d);
}
