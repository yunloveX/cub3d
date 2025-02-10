/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:38:58 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/10 10:57:16 by iestero-         ###   ########.fr       */
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
		mlx_loop(cub3d.mlx);
		mlx_terminate(cub3d.mlx);
		ft_lstclear(&cub3d.hand_frame, free);
		free(cub3d.hand_texture);
	}
	return (0);
}
