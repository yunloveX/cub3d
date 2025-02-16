/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:59:26 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/16 17:17:18 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"
# include "quatlib.h"

# include "linked_list.h"

typedef struct s_map
{
	char	**grid;
	int		**door_states;
	int		width;
	int		height;
}	t_map;

typedef struct s_colors
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
}	t_colors;

typedef struct s_player
{
	t_quaternion	pos;
	t_quaternion	right;
	t_quaternion	down;
	t_quaternion	cam;
}	t_player;

typedef struct s_cub3d
{
	void			*win;
	mlx_t			*mlx;
	t_map			map;
	int32_t			old_x;
	int32_t			old_y;
	t_colors		colors;
	t_player		player;
	t_player		player_old;
	mlx_image_t		*img;
	mlx_texture_t	*img_map;
	mlx_texture_t	*textures[4];
	int				mouse_down;
	int				frames_shown;
	double			jumps[3];
}	t_cub3d;

#endif