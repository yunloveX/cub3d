/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:59:26 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/04 15:46:34 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"
# include "quatlib.h"

typedef struct s_map
{
	char	**grid;
	int     **door_states;
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
	mlx_t			*mlx;
	void			*win;
	mlx_image_t		*img;
	t_map			map;
	mlx_texture_t	*textures[6];
	mlx_image_t		*img_hands;
	t_colors		colors;
	t_player		player;
	t_player		player_old;
	int				mouse_down;
	int 			hand_animation_playing;
	float 			hand_animation_frame;
	int32_t				old_x;
	int32_t				old_y;
	double			jumps[3];
	int				frames_shown;
}	t_cub3d;

#endif