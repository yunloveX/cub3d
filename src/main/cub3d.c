/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:38:58 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/14 09:08:08 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2 || !argv)
		printf("Error\nInvalid number of arguments\n");
	else
	{
		init(&cub3d);
		parse(&cub3d, argv[1]);
		render(&cub3d);
		cub3d.hand_frame = *(cub3d.hand_texture);
		mlx_loop(cub3d.mlx);
		mlx_terminate(cub3d.mlx);
	}
	return (0);
}
