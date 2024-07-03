/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestParseo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:31:16 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 08:33:33 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	int		fd;
	int		f;

	if (argc != 2)
		printf("Error\nInvalid number of arguments\n");
	fd = open(argv[1], O_RDONLY);
	f = parse(fd, &cub3d);
	if (f == EXIT_FAILURE)
		printf("Error\nInvalid map\n");
	for (int i = 0; i < cub3d.map.height; i++)
	{
		for (int j = 0; cub3d.map.grid[i][j] != '\0'; j++)
			printf(" %c ", cub3d.map.grid[i][j]);
		printf("\n");
	}
	printf("Map width: %d\n", cub3d.map.width);
	printf("Map height: %d\n", cub3d.map.height);
	printf("Textures: %p\n", cub3d.textures.north);
	printf("Textures: %p\n", cub3d.textures.south);
	printf("Textures: %p\n", cub3d.textures.east);
	printf("Textures: %p\n", cub3d.textures.west);
	return (0);
}