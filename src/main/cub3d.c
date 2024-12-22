/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:38:58 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/02 18:39:55 by yunlovex         ###   ########.fr       */
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
		parse(&cub3d, argv[1]);
		init(&cub3d);
		render(&cub3d);
		mlx_loop(cub3d.mlx);
		mlx_terminate(cub3d.mlx);
	}
	return (0);
}
