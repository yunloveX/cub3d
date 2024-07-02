/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestParseMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:07:30 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/02 20:43:25 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;
	int		f;

	if (argc != 2)
		printf("Error\nInvalid number of arguments\n");
	fd = open(argv[1], O_RDONLY);
	f = parse_map(fd, &map);
	if (f == EXIT_FAILURE)
		printf("Error\nInvalid map\n");
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; map.grid[i][j] != '\0'; j++)
			printf(" %c ", map.grid[i][j]);
		printf("\n");
	}
	return (0);
}
