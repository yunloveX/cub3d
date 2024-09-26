/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:59:26 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 13:12:29 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"
# include "quatlib.h"

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_walls
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_walls;

typedef struct s_colors
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
}	t_colors;
/*
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;*/

typedef struct s_player
{
	t_quaternion	pos;
	t_quaternion	right;
	t_quaternion	down;
	t_quaternion	cam;
}	t_player;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	void		*win;
	mlx_image_t	*img;
	t_map		map;
	t_walls		textures;
	t_colors	colors;
	t_player	player;
}	t_cub3d;

#endif