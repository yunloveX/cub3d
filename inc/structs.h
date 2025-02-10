/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:59:26 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/10 09:56:56 by iestero-         ###   ########.fr       */
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
	mlx_image_t		*img_hands;
	t_map			map;
	mlx_texture_t	*textures[5];
	t_list			**hand_texture;
	t_colors		colors;
	t_player		player;
	t_player		player_old;
	int				mouse_down;
	int 			hand_playing;
	t_list 			*hand_frame;
	int32_t				old_x;
	int32_t				old_y;
	double			jumps[3];
	int				frames_shown;
}	t_cub3d;

#endif